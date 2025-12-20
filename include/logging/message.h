#ifndef LOGGING_MESSAGE_H
#define LOGGING_MESSAGE_H

#include <ctime>
#include <iostream>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

typedef std::string LoggerName;

typedef struct LogMessage
{
    const time_t curtime = time(0);
    const LogLevel level;
    const LoggerName logger;
    const std::string message;
    operator std::string() const;
} LogMessage;

std::ostream &operator<<(std::ostream &os, const LogMessage &obj);

#endif