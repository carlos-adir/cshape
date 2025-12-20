#ifndef LOGGING_SENDER_H
#define LOGGING_SENDER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include "message.h"
#include "handler.h"
#include "buffer.h"

class MessageSender {
private:
    const std::unique_ptr<Buffer> buffer;
    const LogLevel level;
    const LoggerName name;
    const std::shared_ptr<IHandler> handler;
public:
    MessageSender(const LogLevel level, const LoggerName name, const std::shared_ptr<IHandler>& handler) : level(level), name(name), handler(handler) {};
    ~MessageSender() = default;
    
    template<typename T>
    const MessageSender& operator<<(const T& obj) const;
};

#include "sender_impl.tpp"

#endif