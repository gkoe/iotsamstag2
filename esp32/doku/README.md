# LeoIot ESP

## Ziele
Für das IOT-System der HTBLA Leonding sollen mehrere Geräte (Thing) für, teils KI-unterstützte Steuerungsaufgaben verwendet werden. Ein großer Teil dieser Geräte wird auf Basis der Mikrocontrollerplattformen ESP32/ESP8266 implementiert. Diese Komponenten sind leistungsfähig, preisgünstig und ermöglichen die einfache Einbindung per Wifi und Bluetooth.
Im Zentrum der Entwicklungsarbeiten stehen Bibliotheken, die für die Implementierung der unterschiedlichen Geräte die Basis darstellen und Coderedundanz vermeiden.
Die Kommunikation mit den Things erfolgt primär über einen eingebauten Webserver und eine MQTT-Schnittstelle. Damit es bei dieser Kommunikation zu keinen Verzögerungen kommt, sind alle Bibliotheken so zu implementieren, dass sie den Prozessor nicht blockiern (keine delay()-Aufrufe).

## Bibliotheken und deren Abhängigkeiten

### Basisbibliotheken

- **InternLed** ermöglicht einfache Signalisierungen
- **Logger** mit dem einfachen Loggerziel **SerialLoggerTarget** kann für Logausgaben konfiguriert und verwendet werden
- **ThingTime** verwaltet Datum und Uhrzeit des Geräts 
- **ThingConfig** ist für die Verwaltung von Konfigurationsdaten verantwortlich
- **HttpServer** kümmert sich um die Kommunikation per Wifi und stellt einen einfachen Webserver zur Verfügung, der durch die Registrierung eigener Routen erweiterbar ist
- **MqttClient** kapselt die Verwendung der Mqtt-Kommunikation und stellt eine einfache Schnittstelle zur Verfügung

### Bibliotheken zur Verwaltung von Sensoren und Aktoren

- **Sensor** bietet als Basisklasse die nötigsten Funktionalitäten eines Sensors 
- **Actor** wird als Basisklasse für eigene Aktoren verwendet
- **Thing** verwaltet die im Gerät verwendeten Sensoren und Aktoren

Bibliotheken für Sensoren und Aktoren werden bedarfsgerecht entwickelt:

- **Dht22** blockadefreie Bibliothek zum Auslesen der Temperatur und Luftfeuchtigkeit
- **Mhz14a und Mhz19b** liefern CO2-Werte als Basis für die Beurteilung der Luftqualität
- **Irda** Aktor, mit dem Infrarotsignale versendet werden können. Ein Hilfsprogramm hilft dabei, Codes von Infrarotfernbedienungen auszulesen.
- **PIR** erkennt Bewegungen im Umfeld

### Erweiterte Bibliotheken

Die Protokollierung der Abläufe ist eine, für den Projekterfolg wesentliche Komponente. Daher wird der **Logger** um weitere Logziele erweitert
- **LoggerTargets**
-- **UdpLoggerTarget** verschickt Logmeldungen per Udp (Broadcast oder gezielt) in das Netz
-- **MqttLoggerTarget** verschickt Logmeldungen per Mqtt
-- **FileLoggerTarget** speichert Logmeldungen auf dem Flash-Filesystem des ESP und erlaubt es, diese Logmeldungen nachträglich zu analysieren
-- **DisplayLoggerTarget** ermöglicht die Logausgaben auf den OLED-Displays der ESP32

Zur Auswertung der Logeinträge stehen mehrere Tools zur Verfügung, die es erlauben, empfangene Logmeldungen zu suchen, zu filtern und abzuspeichern
- **WinLogViewer** stellt für einige LoggerTargets eine Oberfläche bereit
-- SerialLoggerTarget mittels Verbindung zum Gerät über die USB-COM-Bridge (COM-Schnittstelle einstellbar)
-- UdpLoggerTarget lauscht auf Logmeldungen, die per Udp empfangen werden
-- FileLoggerTarget ermöglicht das Auslesen der im SPIFFS des ESP gespeicherten Logmeldungen nach Datum und Loglevel
- **WebLogViewer** bietet analoge Auswertemöglichkeiten wie der WinLogViewer (ohne SerialLogger) über eine Webanwendung auf Angular-Basis
- **AndroidLogViewer** wertet die Logmeldungen auf einem Android-Gerät aus

