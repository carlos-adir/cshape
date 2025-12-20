#pragma once

/*
void MessageSender::flush(const std::string& message)
{
    if (handler->is_active)
        handler->write({level: level, logger: name, message: message});
}
*/

template<typename T>
const MessageSender& MessageSender::operator<<(const T& obj) const
{
    if (handler->is_active)
        *buffer << obj;
    return *this;
}

