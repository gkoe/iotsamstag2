#pragma once

#include <SPIFFS.h>
#include <FS.h>
#include <LoggerTarget.h>
#include <list>

struct Message{
    char time[10];
    char type;
	char tag[19];
    char message[70];
};

class FileLoggerTarget : public LoggerTarget
{
    public:
        FileLoggerTarget(const char* name, int type, int size);
        virtual void log(int type, const char* tag, const char* message);
        void setReadingPosition(long time);
        void readLog(char* buffer);
        
    private:
        void saveMessage(Message* m);
        std::list<Message> _message;
        Message* _savePointer;
        Message* _readPosition;
        int _size;
};
