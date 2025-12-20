#ifndef LOGGING_BUFFER_H
#define LOGGING_BUFFER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

const static char ENDL = '\n';

class Buffer
{
private:
    const std::unique_ptr<std::ostringstream> stream = std::make_unique<std::ostringstream>();
public:
    std::string str;
    Buffer() = default;
    void clear();

    template<typename T>
    Buffer& operator<<(const T& obj);
};



#include "buffer_impl.tpp"

#endif