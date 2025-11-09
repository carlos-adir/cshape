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
    const time_t curtime;
    const LogLevel level;
    const std::string logger;
    const std::string message;
    operator std::string() const;
    LogMessage(LogLevel level, const std::string& logger, const std::string& message);
} LogMessage;

std::ostream &operator<<(std::ostream &os, const LogMessage &obj);

class IHandler 
{
    public:
        virtual void write(const LogMessage& message) const = 0;
};

class CoutHandler : public IHandler
{
    public:
        CoutHandler();
        ~CoutHandler();
        void write(const LogMessage& message) const override;
};

class FileHandler : public IHandler
{
    private:
        FileHandler(const std::string& filename);
        std::ofstream& stream;
        
    public:
        const std::string filename;
        ~FileHandler();
        static std::shared_ptr<FileHandler> getInstance(const std::string& filename); 
        void write(const LogMessage& message) const override;
};

class TransmiterHandler : public IHandler
{
    private:
        std::vector<std::shared_ptr<IHandler>> handlers = {};
    public:
        TransmiterHandler();
        ~TransmiterHandler();
        void write(const LogMessage& message) const override;
        bool add(const std::shared_ptr<IHandler> ptr);
        bool remove(const std::shared_ptr<IHandler> ptr);
};

class Logger {
private:
    Logger(const std::string& loggerName);
    
public:
    LogLevel level = LogLevel::DEBUG;
    const std::string name;
    const std::shared_ptr<TransmiterHandler> handler;
    static Logger& getInstance(const std::string& filename);
    void log(const LogLevel level, const std::string &message) const;
    const Logger& operator<<(const std::string& obj) const;
};

#endif