
#include "cshape/loggers.h"

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



Logger::Logger(const std::string& loggerName) : name(loggerName)
{
    std::cout << "Created instance: '" << loggerName << "'" << std::endl;
}


static std::map<const std::string, const std::shared_ptr<Logger>> loggers = {};

Logger& Logger::getInstance(const std::string& loggerName)
{
    std::cout << "Getting instance: " << loggerName.size() << ": '" << loggerName << "'" << std::endl;
    if (!loggers.count(loggerName))
        loggers.insert({loggerName, std::make_shared<Logger>(Logger(loggerName))});
    Logger& logger = *loggers.at(loggerName);
    std::cout << "Got instance: " << logger.name << ": '" << &logger << "'" << std::endl;
    return logger;
}


void Logger::log(const LogLevel level, const std::string& message) const
{
    const LogMessage logMessage = {time(0), level, name, message};
}

