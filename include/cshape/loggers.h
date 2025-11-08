// C++ program to implement a basic logging system.
#ifndef LOGGERS_H
#define LOGGERS_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

typedef struct LogMessage
{
    const time_t time;
    const LogLevel level;
    const std::string logger;
    const std::string message;
} LogMessage;

std::ostream &operator<<(std::ostream &os, const LogMessage &obj);


class IHandler 
{
    public:
        virtual void write(const LogMessage message) const = 0;
};

class TransmiterHandler : public IHandler
{
    private:
        std::vector<IHandler> handlers = {};
    public:
        TransmiterHandler();
        void write(const LogMessage message) const override;
};

class Logger {
private:
    Logger(const std::string& loggerName);
    
public:
    const std::string name;
    static Logger& getInstance(const std::string& filename);
    void log(const LogLevel level, const std::string &filename) const;
};

#endif