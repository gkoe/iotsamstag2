
#include "Logger.h"

/*
	Ein Logeintrag mit folgenden Parametern wird zum Server geschickt:
	topic: Topic, für das der LogEntry ausgelöst wurde
	type: Typ der Logmessage (Info - Fatalerror)
	time: Unix-Timecode
	message: Logtext
*/

void LoggerClass::init(const char* name) {
	strcpy(_name, name);
	Serial.print(F("TH* Thing init with name: "));
	Serial.println(_name);
}

void LoggerClass::info(const char* tag, const char* message) {
	log(LOG_LEVEL_INFO, tag, message);
}

void LoggerClass::debug(const char* tag, const char* message) {
	log(LOG_LEVEL_DEBUG, tag, message);
}

void LoggerClass::exception(const char* tag, const char* message) {
	log(LOG_LEVEL_EXCEPTION, tag, message);
}

void LoggerClass::error(const char* tag, const char* message) {
	log(LOG_LEVEL_ERROR, tag, message);
}

void LoggerClass::fatalerror(const char* tag, const char* message) {
	log(LOG_LEVEL_FATALERROR, tag, message);
}

void LoggerClass::log(int logLevel, const char* tag, const char* message) {
	for (std::list<LoggerTarget *>::iterator it = _logger.begin(); it != _logger.end(); ++it)
	{
		// Serial.print(F("*NO: refresh, Sensor: "));
		// Serial.print(it->first);
		// Serial.print(F(", last Value: "));
		// Serial.println(it->second->getLastMeasurement());
		LoggerTarget *loggerTarget = *it;
		if(logLevel >= loggerTarget -> getLogLevel()) {
			loggerTarget->log(_logLevelTexts[logLevel], tag, message);
		}
	}
}

void LoggerClass::addLoggerTarget(LoggerTarget* logger) {
	_logger.push_back(logger);
}

const char* LoggerClass::getLogLevelText(int logLevel){
	return _logLevelTexts[logLevel];
}


LoggerTarget* LoggerClass::getLoggerTarget(const char* name) {
	for (std::list<LoggerTarget *>::iterator it = _logger.begin(); it != _logger.end(); ++it)
	{
		// Serial.print(F("*NO: refresh, Sensor: "));
		// Serial.print(it->first);
		// Serial.print(F(", last Value: "));
		// Serial.println(it->second->getLastMeasurement());
		LoggerTarget *logger = *it;
		if(strcmp(logger->getName(), name) == 0) {
			return logger;
		}
	}
	return nullptr;
}

char * LoggerClass::getName() {
	return _name;
}
LoggerClass Logger;

