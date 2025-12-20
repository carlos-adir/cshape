#pragma once


template<typename T>
const MessageSender& MessageSender::operator<<(const T& obj) const
{
    if (handler->is_active)
    {
        *buffer << obj;
        if (buffer->str.back() == ENDL && handler != nullptr && handler->is_active)
            handler->write({level: level, logger: name, message: buffer->str.substr(0, buffer->str.size()-1)});
    }
    return *this;
}

