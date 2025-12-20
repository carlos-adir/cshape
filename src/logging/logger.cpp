
#include "cshape/logging.h"

Logger::Logger(const std::string& loggerName) : name(loggerName)
{
    size_t i = loggerName.size() - 1;
    for (; i>0; --i)
        if (loggerName[i] == '.')
            break;
    if (i > 0)
    {
        const std::string parentName = loggerName.substr(0, i);
        Logger& parent = getInstance(parentName);
        // *this += parent;
    }
    else
    {   
        // *handler += std::make_shared<CoutHandler>();
        // *handler += FileHandler::getInstance(loggerName + ".log");
    }
}

Logger::~Logger(){};


static std::unique_ptr<std::map<const std::string, const std::shared_ptr<Logger>>> loggers;

Logger& Logger::getInstance(const std::string& loggerName)
{
    if (loggers == nullptr)
        loggers = std::make_unique<std::map<const std::string, const std::shared_ptr<Logger>>>();
    if (!loggers->count(loggerName))
        loggers->insert({loggerName,
                        std::shared_ptr<Logger>(new Logger(loggerName))});
    return *loggers->at(loggerName);
}


void Logger::log(const LogLevel level, const std::string& message) const
{
}
