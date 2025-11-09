
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
    tm* timeinfo = localtime(&obj.curtime);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
             "%Y-%m-%d %H:%M:%S", timeinfo);

    os << '[' << timestamp << "] ";
    os << levelToString(obj.level) << ": ";
    os << '(' << obj.logger << ')';
    os << obj.message;
    return os;
}
LogMessage::LogMessage(LogLevel level, const std::string& logger, const std::string& message) : curtime(time(0)), level(level), logger(logger), message(message)
{

}

LogMessage::operator std::string() const
{
    std::ostringstream ss;
    tm* timeinfo = localtime(&curtime);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
             "%Y-%m-%d %H:%M:%S", timeinfo);

    ss << '[' << timestamp << "] ";
    ss << levelToString(level) << ": ";
    ss << '(' << logger << ')';
    ss << message;
    return ss.str();
};

CoutHandler::CoutHandler(){}

CoutHandler::~CoutHandler(){}


void CoutHandler::write(const LogMessage& message) const
{
    std::cout << message << std::endl;
}


FileHandler::FileHandler(const std::string& filename) : filename(filename), stream(*new std::ofstream(filename))
{
}

FileHandler::~FileHandler()
{
    stream.close();
    delete &stream;
}


void FileHandler::write(const LogMessage& message) const
{
    std::cout << "Writing on file: '" << filename << "'" << std::endl;
    stream << std::string(message) << std::endl;
}


static std::map<const std::string, const std::shared_ptr<FileHandler>> files = {};

std::shared_ptr<FileHandler> FileHandler::getInstance(const std::string& filename)
{
    std::cout << "Getting filehandler instance: " << filename.size() << ": '" << filename << "'" << std::endl;
    if (!files.count(filename))
        files.insert({filename, std::shared_ptr<FileHandler>(new FileHandler(filename))});
    std::shared_ptr<FileHandler> handler = files.at(filename);
    std::cout << "Got filehandler instance: " << handler->filename << ": '" << handler << "'" << std::endl;
    return handler;
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
        if (ptr == handler)
            return false;
    this->handlers.push_back(ptr);
    return true;
}

bool TransmiterHandler::remove(const std::shared_ptr<IHandler> ptr)
{
    for (size_t i = 0; i < handlers.size(); ++i)
        if (handlers[i] == ptr)
        {
            handlers.erase(handlers.begin() + i);
            return true;
        }
    return false;
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
        handler->add(std::make_shared<CoutHandler>());
        std::cout << "Adding file" << std::endl;
        handler->add(FileHandler::getInstance(loggerName + ".log"));
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
    LogMessage logmes = {level, name, message};
    handler->write(logmes);
}

const Logger& Logger::operator<<(const std::string& message) const
{
    LogMessage logmes = {this->level, name, message};
    handler->write(logmes);
    return *this;
}
