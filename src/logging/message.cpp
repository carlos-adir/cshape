
#include "cshape/logging.h"
#include <fstream>


const char* levelToString(LogLevel level){
    switch (level)
    {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::CRITICAL:
            return "CRITICAL";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            throw std::invalid_argument("Out of options");
    }
}


std::ostream &operator<<(std::ostream &os, const LogMessage &obj){
    tm* timeinfo = localtime(&obj.curtime);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
             "%Y-%m-%d %H:%M:%S", timeinfo);

    os << '[' << timestamp << "] ";
    os << levelToString(obj.level) << ": ";
    os << '(' << obj.loggerName <<')';
    os << obj.message;
    return os;
}
