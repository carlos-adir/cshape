
#include "cshape/loggers.h"
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

StreamHandler::StreamHandler(){}

StreamHandler::~StreamHandler(){}


void StreamHandler::write(const LogMessage& message) const
{
    std::cout << message << std::endl;
}

TransmiterHandler::TransmiterHandler(){}

TransmiterHandler::~TransmiterHandler(){}


void TransmiterHandler::write(const LogMessage& message) const
{
    for (const auto& handler : handlers)
        handler->write(message);
}

bool TransmiterHandler::add(const std::shared_ptr<IHandler> ptr)
{
    for (const auto& handler : handlers)
    {
        std::cout << "---- he" << std::endl;
        if (ptr == handler)
        {
            std::cout << "----     ha" << std::endl;
            std::cout << "----     Handler is already included" << std::endl;
        }
    }
    this->handlers.push_back(ptr);
    std::cout << "Got here" << std::endl;
    return true;
}

Logger::Logger(const std::string& loggerName) : name(loggerName), handler(std::make_shared<TransmiterHandler>())
{
    std::cout << "Created instance: '" << loggerName << "'" << std::endl;
    size_t i = loggerName.size() - 1;
    for (; i>0; --i)
        if (loggerName[i] == '.')
            break;
    if (i > 0)
    {
        std::cout << "Adding handler" << std::endl;
        const std::string parentName = loggerName.substr(0, i);
        Logger& parent = getInstance(parentName);
        handler->add(parent.handler);
    }
    else
    {   
        std::cout << "Adding cout" << std::endl;
        handler->add(std::make_shared<StreamHandler>());
    }
}


static std::map<const std::string, const std::shared_ptr<Logger>> loggers = {};

Logger& Logger::getInstance(const std::string& loggerName)
{
    std::cout << "Getting instance: " << loggerName.size() << ": '" << loggerName << "'" << std::endl;
    if (!loggers.count(loggerName))
        loggers.insert({loggerName,
                        std::shared_ptr<Logger>(new Logger(loggerName))});
    Logger& logger = *loggers.at(loggerName);
    std::cout << "Got instance: " << logger.name << ": '" << &logger << "'" << std::endl;
    return logger;
}


void Logger::log(const LogLevel level, const std::string& message) const
{
    handler->write({time(0), level, name, message});
}

