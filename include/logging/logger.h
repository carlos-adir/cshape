#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include "message.h"
#include "handler.h"



class Logger : public TransmiterHandler {
private:
    Logger(const std::string& loggerName);

public:
    ~Logger();
    const LoggerName name;
    static Logger& getInstance(const std::string& filename);
    
    void log(const LogLevel level, const std::string &message) const;
    template<typename T>
    const Logger& operator<<(const T& obj) const {
        return *this;
    }
};

#endif