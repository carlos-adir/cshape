#ifndef LOGGING_TYPES_H
#define LOGGING_TYPES_H

#include <ctime>
#include <iostream>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

typedef std::string LoggerName;

typedef time_t Time;

typedef std::string Message;

typedef std::string Filepath;


class Logger;

#endif