#pragma once



inline void Buffer::flush()
{
    if (this->flusher != nullptr)
        this->flusher(str.substr(0, str.size()-1));
    clear();
}

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
    if (str.back() == ENDL)
        this->flush();
    return *this;
}
