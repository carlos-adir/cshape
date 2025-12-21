#ifndef LOGGING_MESSAGE_H
#define LOGGING_MESSAGE_H

#include "types.h"

typedef struct LogMessage
{
    const Time curtime = time(0);
    const LogLevel level;
    const LoggerName loggerName;
    const Message message;
    
    LogMessage(const LogLevel level, const LoggerName& loggerName, const Message& message) : level(level), loggerName(loggerName), message(message) {};
} LogMessage;

std::ostream &operator<<(std::ostream &os, const LogMessage &obj);

#endif