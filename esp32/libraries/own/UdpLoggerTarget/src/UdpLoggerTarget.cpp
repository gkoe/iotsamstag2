#include "UdpLoggerTarget.h"
#include <Arduino.h>
#include <Thing.h>
#include <ThingConfig.h>
#include <ThingTime.h>

/**
 * Ermittelt aus der aktuellen IP-Adresse die Broadcastadresse, die im letzten Byte
 * FF enthält.
 */
uint32_t getBroadcastIp(){
	tcpip_adapter_ip_info_t ipInfo; 
	tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo); 
	uint32_t broadcastAddress = ipInfo.ip.addr % (16777216) + 4278190080u; //(255*256*256*256);
	Serial.printf("*UT Broadcast-IP: %x\n", broadcastAddress);
	return broadcastAddress;
}

UdpLoggerTarget::UdpLoggerTarget(const char* name, int logLevel)
    :LoggerTarget(name, logLevel){
	Serial.printf("*UT In UdpLoggerTarget Constructor without ip\n");
	const char* udpTargetIpText = ThingConfig.getValue("udploggerip");
 	const char* udpPortText = ThingConfig.getValue("udploggerport");
	if( strlen(udpTargetIpText) == 0 || strlen(udpPortText) == 0){
  		Serial.println("*ULT No Ip or no port");
		_ip = IPAddress(getBroadcastIp());
		_port = 49155;
	}
	else{
		_ip.fromString(udpTargetIpText);
		_port = atoi(udpPortText);
  		Serial.println("*ULT ip and port from ThingConfig");
	}
	const char* ipAddrText = _ip.toString().c_str();
	Serial.printf("*ULT Udp-TargetAddress: %s, Port: %d\n", ipAddrText, _port);
}

void UdpLoggerTarget::log(const char* logLevelText, const char* tag, const char* message){
    _udp.beginPacket(_ip, _port);
	char logMessage[256];
	const char* thingName = Thing.getName();
	char timeText[40];
	ThingTime.getTextDateTime(timeText);
	// Serial.printf("*ULT Thingname: %s\n", thingName);
	sprintf(logMessage, "*LG: %s;%s;%s;%s;%s\n", timeText, thingName, logLevelText,tag, message);
	int length = _udp.printf(logMessage);
	_udp.endPacket();
	Serial.printf("*ULT Sent Udp-Logmessage, length: %d, Text: %s",length,logMessage);
}
