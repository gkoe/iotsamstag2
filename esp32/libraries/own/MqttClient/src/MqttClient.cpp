#include "MqttClient.h"
#include <ThingConfig.h>

/*
* Zentrale Callbackroutine, die alle Nachrichten der registrierten
* Subscriber empfängt und dann an die Callbackmethode des 
* Subscribers weiterleitet
* Reine C-Funktion ohne direkten Zugriff auf fields und methods
* Kommunikation über Singleton.
*/

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  char payloadText[length+1];
  for (int i = 0; i < length; i++)
  {
    payloadText[i] = (char)payload[i];
  }
  payloadText[length] = 0;
  Serial.print(F("*MC: Message arrived ["));
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(payloadText);
  MqttClient.notifySubscribers(topic, payloadText);
}


/**
 * Beginnt der Text mit den Zeichen des Patterns?
 */
bool strStartsWith(char *text, char *pattern)
{
  int length = strlen(pattern);
  if (strlen(text) < length)
  {
    return false;
  }
  for (int i = 0; i < length; i++)
  {
    if (text[i] != pattern[i])
      return false;
  }
  return true;
}

/**
 * Überprüft, welche Subscriber das Topic registriert haben und 
 * verständigt die entsprechenden Subscriber.
 * //! Derzeit wird nur überprüft ob das empfangene Topic mit dem registrierten
 *      Text beginnt. Später auch um Wildcards erweitern (Readme.md auch updaten).
 */
void MqttClientClass::notifySubscribers(char *topic, char *payload)
{
  for (std::list<MqttSubscription *>::iterator it = _mqttSubscriptions.begin(); it != _mqttSubscriptions.end(); it++)
  {
    MqttSubscription *subscriptionPtr = *it;
    Serial.println(topic);
    Serial.println(subscriptionPtr->topic);
    if (strStartsWith(topic, subscriptionPtr->topic))
    {
      subscriptionPtr->subscriberCallback(topic, payload);
    }
  }
}

// MqttCallback* MqttClientClass::getSubscriberCallback(){
//   return _subscriberCallback;
// }

void MqttClientClass::addSubscription(MqttSubscription *subscriptionPtr)
{
  char subscriptionTopic[80];
  sprintf(subscriptionTopic, "%s/command", subscriptionPtr->topic);
  strcpy(subscriptionPtr->topic, subscriptionTopic);
  _mqttSubscriptions.push_back(subscriptionPtr);
  Serial.print(F("*MC: Subscription: "));
  Serial.println(subscriptionPtr->topic);
}

/**
 * Verbindung mit dem MQTT-Broker initialisieren
 */
void MqttClientClass::init(const char *mainTopic)
{
  strcpy(_mainTopic, mainTopic);
  const char* configText = ThingConfig.getValue("server");
  strcpy(_mqttServer, configText);
  configText = ThingConfig.getValue("user");
  strcpy(_mqttUserName, configText);
  configText = ThingConfig.getValue("password");
  strcpy(_mqttPassword, configText);
  configText = ThingConfig.getValue("thingname");
  strcpy(_mqttThingName, configText);
  configText = ThingConfig.getValue("port");
  _mqttPort = atoi(configText);
  configText = ThingConfig.getValue("lastwill");
  if(strcmp(configText, "true") == 0) {
     sprintf(_lastWillTopic,"%s/thing/lastwill", _mqttThingName);
  }
  else{
    strcpy(_lastWillTopic,"");
  }
  Serial.printf("*MC: MQTT-Broker Address: %s:%i\n", _mqttServer, _mqttPort);
  _mqttClient.setClient(_wifiClient); // braucht er statisch
	_mqttClient.setServer(_mqttServer, _mqttPort);
  _mqttClient.setCallback(mqttCallback);
  Serial.println(F("*MC: MqttClient started"));
  reconnect();
}

/**
 * Alle registrierten Subscriptions müssen beim reconnect()
 * neu angemeldet werden.
 */
void MqttClientClass::subscribeToBroker()
{
  Serial.println(F("*MC: subscribe to broker"));
  Serial.printf("*MC: subscribeToBroker(), isConnected: %d\n", _mqttClient.connected());
  // Alle subscriptions wieder anmelden
  for (std::list<MqttSubscription *>::iterator it = _mqttSubscriptions.begin();
        it != _mqttSubscriptions.end(); it++)
  {
    MqttSubscription *subscriptionPtr = *it;
    _mqttClient.subscribe(subscriptionPtr->topic);
    Serial.print(F("*MC: Subscribe for Topic: "));
    Serial.println(subscriptionPtr->topic);
  }
}

/**
 * Versuchen, die Verbindung zum MQTT-Broker wieder
 * aufzubauen. Subscriber wieder anmelden
 */
void MqttClientClass::reconnect()
{
  if(strlen(_mqttServer) < 5){
    return;
  }
  Serial.printf("*MC: reconnect MQTT: %s \n", _mqttServer);
  if(_mqttClient.connected()){
    Serial.print(F("*MC: reconnect(), mqttclient was connected\n"));
  }
  Serial.print(F("*MC: reconnect(), BLOCKING for 20 seconds\n"));
  bool connectIsOk; 
  if(strlen(_mqttUserName) > 0 && strlen(_mqttPassword) > 0){
    if(strlen(_lastWillTopic) == 0){  // User und kein LastWill
      connectIsOk = _mqttClient.connect(_mqttThingName,  _mqttUserName, _mqttPassword);
    }
    else{  // User und LastWill
      connectIsOk = _mqttClient.connect(_mqttThingName,  _mqttUserName, _mqttPassword, _lastWillTopic, 1, true, "offline" );
    }
  }
  else{  // kein User und Password
    if(strlen(_lastWillTopic) == 0){  // kein User und kein LastWill
      connectIsOk = _mqttClient.connect(_mqttThingName);
    }
    else{  // kein User aber LastWill
      connectIsOk = _mqttClient.connect(_mqttThingName, _lastWillTopic, 1, true, "offline" );
    }
  }
  Serial.printf("*MC reconnect(), Connect is ok: %d\n", connectIsOk);
  if (_mqttClient.connected())
  {
    Serial.println(F("*MC: reconnect(), MqttClient is now connected"));
    subscribeToBroker();
  }
  else
  {
    Serial.println(F("!MC: reconnect(); MqttClient IS NOT connected"));
  }
  Serial.printf("*MC: reconnect() end, isConnected: %d, millis: %lu\n", _mqttClient.connected(),millis());
}

/**
 * Für das Topic wird die payload an den Broker übertragen
 */
void MqttClientClass::publish(char *topic, char *payload)
{
  if (!_mqttClient.connected())
  {
    Serial.println(F("!MC: publish(), mqtt client not connected"));
  }
  else
  {
    Serial.print(F("*MC: Topic: "));
    Serial.print(topic);
    Serial.print(F(", Payload: "));
    Serial.print(payload);
    Serial.println(F(" published"));
    // publish with retained-flag
    _mqttClient.publish(topic, payload, true);
  }
}

/**
 * MqttClient-Verbindung aufrecht erhalten.
 * Wurde die Verbindung unterbrochen, reconnect versuchen
 */
void MqttClientClass::doLoop()
{
    if(strlen(_mqttServer) < 5){
    return;
  }
  // if connection lost ==> try to reconnect
  if (!_mqttClient.connected())
  {
    if (millis() - _lastReconnectAttempt > 60000)  // nur alle 60 Sekunden reconnect versuchen
    {
      Serial.printf("!MC: doLoop(): MQTT Client not connected, millis: %lu\n", _lastReconnectAttempt);
      _lastReconnectAttempt = millis();
      reconnect();
      Serial.printf("*MC: doLoop() after reconnect, isConnected: %d\n", _mqttClient.connected());
      _mqttClient.loop();
      // if (reconnect())   //! führt zu häufigen reconnects
      // {
      //   _lastReconnectAttempt = 0;
      // }
    }
  }
  else
  {
    //Serial.println("*MC: MQTT Client doLoop()");
    _mqttClient.loop();
  }
}

// Quasi Singletonimplementierung
MqttClientClass MqttClient;
