#ifndef LOGGING_BUFFER_H
#define LOGGING_BUFFER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

const static char ENDL = '\n';

using ISendMessage = void (*)(const std::string &);

class Buffer
{
private:
    const ISendMessage flusher;
    const std::unique_ptr<std::ostringstream> stream = std::make_unique<std::ostringstream>();
public:
    std::string str;
    Buffer(const ISendMessage flusher) : flusher(flusher) {};
    void flush();
    void clear();

    template<typename T>
    Buffer& operator<<(const T& obj);
};



#include "buffer_impl.tpp"

#endif