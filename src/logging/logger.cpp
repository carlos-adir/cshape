
#include "cshape/logging.h"


static std::unique_ptr<std::map<const LoggerName, const std::shared_ptr<Logger>>> loggers;


Logger::Logger(const LoggerName& loggerName) :
    name(loggerName),
    debug(LogLevel::DEBUG, loggerName)
{
    size_t i = loggerName.size() - 1;
    for (; i>0; --i)
        if (loggerName[i] == '.')
            break;
    if (i > 0)
    {
        const LoggerName parentName = loggerName.substr(0, i);
        *this += getInstance(parentName);
    }
    else
    {   
        *this += std::make_shared<CoutHandler>();
        *this += FileHandler::getInstance(loggerName + ".log");
    }
}

Logger::~Logger(){};


std::shared_ptr<Logger> Logger::getInstance(const LoggerName& loggerName)
{
    if (loggers == nullptr)
        loggers = std::make_unique<std::map<const LoggerName, const std::shared_ptr<Logger>>>();
    if (!loggers->count(loggerName))
    {
        auto newLogger = std::shared_ptr<Logger>(new Logger(loggerName));
        loggers->insert({loggerName, newLogger});
    }
    return loggers->at(loggerName);
}
