// C++ program to implement a basic logging system.

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>

// Enum to represent log levels
enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };


typedef struct LogMessage
{
    const time_t time;
    const LogLevel level;
    const std::string logger;
    const std::string message;
} LogMessage;


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
    tm* timeinfo = localtime(&obj.time);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
             "%Y-%m-%d %H:%M:%S", timeinfo);

    os << '[' << timestamp << "] ";
    os << levelToString(obj.level) << ": ";
    os << '(' << obj.logger << ')';
    os << obj.message;
    return os;
}

//
//
//
//
//
//
//   HANDLERS
//
//
//
//
//
//

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
        void write(const LogMessage message) const;
};

//
//
//
//
//
//
//   LOGGER
//
//
//
//
//
//

class Logger {
private:
    static std::map<const std::string, Logger> instances;
    Logger(const std::string& loggerName);  // Now private
    
public:
    const std::string name;
    static Logger& getInstance(const std::string& filename);
    void log(const LogLevel level, const std::string &filename) const;
};


Logger::Logger(const std::string& loggerName) : name(loggerName)
{
    std::cout << "Created instance: '" << loggerName << "' at " << (size_t)&(*this) << std::endl;

}

std::map<const std::string, Logger> Logger::instances;

Logger& Logger::getInstance(const std::string& loggerName)
{
    std::cout << "Getting instance: " << loggerName.size() << ": '" << loggerName << "'" << std::endl;
    if (!instances.count(loggerName))
        instances.insert({loggerName, Logger(loggerName)});
    return instances.at(loggerName);
}


void Logger::log(const LogLevel level, const std::string& message) const
{
    const LogMessage logMessage = {time(0), level, name, message};
}

