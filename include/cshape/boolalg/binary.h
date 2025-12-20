#ifndef BOOLALG_BINARY_H
#define BOOLALG_BINARY_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <cstring>

typedef std::uint8_t byte;
typedef unsigned char itetype;

class Binary
{
private:
    explicit Binary(const std::vector<byte> bytes, const itetype nbits);

public:
    std::vector<byte> bytes;
    itetype nbits;
    
    Binary(const Binary& other);
    
    explicit Binary(const byte number, const itetype nbits = 0);


    operator bool() const noexcept;

    Binary& operator<<=(const itetype n);
    Binary& operator>>=(const itetype n);
    Binary operator|(const Binary& other) const;
    Binary operator&(const Binary& other) const;
    Binary operator^(const Binary& other) const;

    bool operator==(const Binary& other) const;

    friend std::ostream &operator<<(std::ostream &os, const Binary &obj);   
};

#endif
