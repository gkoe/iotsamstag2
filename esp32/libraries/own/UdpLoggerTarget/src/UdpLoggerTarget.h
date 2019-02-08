#pragma once

#include <LoggerTarget.h>
#include <WiFiUdp.h>

class UdpLoggerTarget : public LoggerTarget
{
    public:
        /**
         * Udp-Logmeldungen werden standardmäßig an Broadcast-IP-Addresse (z.B. 10.0.0.255)
         * und an Portnummer 49155 gesendet.
         * Über ThingConfig kann sowohl die Ip-Adresse (udploggerip) als
         * auch die Portnunmmer (udploggerport) konfiguriert werden.
         */
        UdpLoggerTarget(const char* name, int logLevel);
        
        /**
         * Die Logmeldung wird per UDP verschickt
        */
        virtual void log(const char* logLevelText, const char* tag, const char* message);
        
    private:
        WiFiUDP _udp;
        IPAddress _ip;
        int _port;
};
