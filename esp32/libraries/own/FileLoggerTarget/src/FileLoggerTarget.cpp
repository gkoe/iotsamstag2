#include "FileLoggerTarget.h"
#include <SPIFFS.h>
#include <FS.h>

FileLoggerTarget::FileLoggerTarget(const char* name, int type, int size)
    :LoggerTarget(name, type) {
    _size = size;
    if(SPIFFS.begin(true)) {
        if(SPIFFS.exists("/log.txt")) {
            File file = SPIFFS.open("/log.txt", FILE_READ);
            /*char log[100];
            int x = 0;
            while(file.available()) {
                char y = (char)file.read();
                log[x] = y;
                x++;
                if(y == "\0"){
                    Message m;
                    strncpy(m.time, log, 10);
                    
                }
            }*/
            file.close();
        } else {
          File file = SPIFFS.open("/log.txt", FILE_WRITE);
          file.close();
        }
    }
}

void FileLoggerTarget::log(int type, const char* tag, const char* message){
  Message m;
  strcpy(m.time, (char*)time);
  Serial.printf("*LG: %s => [ %i ] => %s \n", tag, type, message);
  m.type = (char)type;
  if(sizeof(message) > 69){
    char logMessage[70];
    strncpy(logMessage, message, 69);
    logMessage[69] = '\0';
    strcpy(m.message, logMessage);
  } else {
    strcpy(m.message, message);
    strcat(m.message, "\0");
  }
	if(sizeof(tag) > 18){
		char tagMessage[19];
		strncpy(tagMessage, tag, 18);
		tagMessage[18] = '\0';
    strcpy(m.tag, tagMessage);
	} else {
    strcpy(m.tag, tag);
    strcat(m.tag, "\0");
  }
  _message.push_back(m);
  saveMessage(&m);
}

void FileLoggerTarget::saveMessage(Message* m){
  if(SPIFFS.begin(true)) {
    if(SPIFFS.exists("/log.txt")) {
      File f = SPIFFS.open("/log.txt", FILE_APPEND);
      if(f) {
        char saveMessage[101];
        Serial.println(m->time);
        strcpy(saveMessage, m->time);
        saveMessage[11] = m->type;
        strcat(saveMessage, m->tag);
        strcat(saveMessage, m->message);
        Serial.println(saveMessage);
        /*if(f.print(saveMessage)){
    			Serial.println("File content was written");
					Serial.println(f.size());
  			} else {
    			Serial.println("File append failed");
  			}*/
        f.close();
      }
    }
  }
}

char* getPartofCharArray(char* text, int start, int last) {
	int length = last - start;
	char part[length];
	for(int i = 0; i < length; i++) {
		part[i] = text[start+i];
	}
	return part;
} 

void readLoggerFile() {

}
