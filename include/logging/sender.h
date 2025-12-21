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
    const std::unique_ptr<Buffer> buffer = std::make_unique<Buffer>();
    const LogLevel level;
    const LoggerName name;
    mutable std::weak_ptr<IHandler> handler;
public:
    MessageSender() :
        level(LogLevel::DEBUG),
        name("") {};
    MessageSender(const LogLevel level, const LoggerName name) :
        level(level),
        name(name) {};
    ~MessageSender() = default;
    
    template<typename T>
    const MessageSender& operator<<(const T& obj) const
    {
        const auto tmp = handler.lock();
        if (tmp && tmp->is_active)
        {
            *buffer << obj;
            if (!buffer->empty() && buffer->last() == ENDL)
            {
                const LogMessage msg(level, name, buffer->str.substr(0, buffer->str.size()-1));
                tmp->write(msg);
                buffer->clear();
            }
        }
        return *this;
    }

    friend class Logger;
};

#endif