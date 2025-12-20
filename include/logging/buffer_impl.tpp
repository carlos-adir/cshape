#pragma once



inline void Buffer::clear()
{
    stream->str("");
    stream->clear();
}


template<typename T>
Buffer& Buffer::operator<<(const T& obj)
{
    stream << obj;
    str = stream->str();
    return *this;
}
