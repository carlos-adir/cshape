#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include "handler.h"
#include "sender.h"

class Logger : public TransmiterHandler {
private:
    Logger(const LoggerName& loggerName);

public:
    ~Logger();
    const LoggerName name;
    static std::shared_ptr<Logger> getInstance(const LoggerName& filename);

    const MessageSender debug;
};

#endif