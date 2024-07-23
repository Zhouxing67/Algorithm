#include "StreamBItIn.h"
#include <iostream>
int alg4::util::StreamBitIn::readByte(char& byte)
{
    if (is_.eof()) {
        byte = '\0';
        return 0;
    }
    size_t high = 8 - count_, low = count_;
    char highbits = buffer_ << low;
    byte = highbits;

    is_.get(buffer_);
    char lowbits = buffer_ >> high;
    byte |= lowbits;
    return 8;
}

int alg4::util::StreamBitIn::readBit(bool& bit)
{

    if (count_ == 8) {
        std::cout << "buffer full" << std::endl;
        if (is_.eof()) {
            return 0;
        }
        is_.get(buffer_);
        count_ = 0;
    }
    bit = buffer_ >> (7 - count_) & 1;
    count_++;
    return 1;
}