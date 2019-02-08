#include<LoggerTarget.h>
#include<string.h>


LoggerTarget::LoggerTarget(const char *loggerName, int logLevel) {
    strcpy(_loggerName, loggerName);
    _logLevel = logLevel;
}

char * LoggerTarget::getName() {
    return _loggerName;
}

int LoggerTarget::getLogLevel() {
    return _logLevel;
}

void LoggerTarget::setLogLevel(int type) {
    _logLevel = type;
}