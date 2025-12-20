
#include "cshape/boolalg/binary.h"
#include <iostream>

static const std::uint8_t sizet = 8 * sizeof(byte);


Binary::Binary(const std::vector<byte> bytes, const itetype nbits): bytes(bytes), nbits(nbits) {};

Binary::Binary(const Binary& other) : bytes(other.bytes), nbits(other.nbits) {};

template<typename T>
std::vector<byte> as_bytes(const T& value, const itetype nbits)
{
    std::vector<byte> buffer;
    const unsigned char sizet = 8 * sizeof(byte);
    const unsigned char qtt = (nbits/sizet) + (nbits % sizet ? 1 : 0);
    std::memcpy(buffer.data(), &value, qtt);
    return buffer;
}

Binary::Binary(const byte number, const itetype nbits) : bytes({number}), nbits(nbits){};



Binary::operator bool() const noexcept
{
    for (const auto b : bytes)
        if (b)
            return true;
    return false;
}

Binary& Binary::operator<<=(const itetype shift)
{
    for (auto& b : bytes)
    {
        b <<= shift;
    }
    return *this;
}

Binary& Binary::operator>>=(const itetype shift)
{
    for (auto& b : bytes)
    {
        b >>= shift;
    }
    return *this;
}

Binary Binary::operator|(const Binary& other) const 
{
    if (this->nbits != other.nbits)
    {
        std::cout << (int)this->nbits << " != " << (int)other.nbits << std::endl;
        std::cout << *this << " != " << other << std::endl;
        throw std::invalid_argument("Or Different bits");
    }
    std::vector<byte> newbs;
    newbs.reserve(this->bytes.size());
    for (itetype i = 0; i < this->bytes.size(); i++)
        newbs.push_back(this->bytes[i] | other.bytes[i]);
    return Binary(newbs, this->nbits);
}

Binary Binary::operator&(const Binary& other) const 
{
    if (this->nbits != other.nbits)
    {
        std::cout << (int)this->nbits << " != " << (int)other.nbits << std::endl;
        std::cout << *this << " != " << other << std::endl;
        throw std::invalid_argument("And Different bits");
    }
    std::vector<byte> newbs;
    newbs.reserve(bytes.size());
    for (itetype i = 0; i < this->bytes.size(); i++)
        newbs.push_back(bytes[i] & other.bytes[i]);
    return Binary(newbs, this->nbits);
}

Binary Binary::operator^(const Binary& other) const 
{
    if (this->nbits != other.nbits)
    {
        std::cout << (int)this->nbits << " != " << (int)other.nbits << std::endl;
        std::cout << *this << " != " << other << std::endl;
        throw std::invalid_argument("Xor Different bits");
    }
    std::vector<byte> newbs;
    newbs.reserve(bytes.size());
    for (itetype i = 0; i < this->bytes.size(); i++)
        newbs.push_back(bytes[i] ^ other.bytes[i]);
    return Binary(newbs, this->nbits);
}


bool Binary::operator==(const Binary& other) const 
{
    if (this->nbits != other.nbits)
    {
        std::cout << (int)this->nbits << " != " << (int)other.nbits << std::endl;
        std::cout << *this << " != " << other << std::endl;
        throw std::invalid_argument("Equal Different bits");
    }
    for (itetype i = 0; i < this->bytes.size(); i++)
        if (this->bytes[i] != other.bytes[i])
            return false;
    return true;
}

std::ostream &operator<<(std::ostream &os, const Binary &obj)
{
    unsigned char size = obj.nbits % sizet;
    char index = obj.nbits / sizet;
    if (size == 0)
    {
        size = sizet;
    }
    else
    {
        index++;
    }

    for (auto i = index - 1; index > 0; index--)
    {
        for (byte k = 1u << (size - 1); k > 0; k >>= 1)
            os << (bool(obj.bytes[i] & k) ? '1' : '0');
        size = sizet;
    }
    return os;
};
