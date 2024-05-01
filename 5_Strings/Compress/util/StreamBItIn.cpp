#include "StreamBItIn.h"
#include <stdio.h>
int alg4::util::StreamBitIn::readByte(char & byte)
{
    size_t high = 8 - count_, low = count_;
    char highbits = buffer_ << low;
    byte = highbits;
    if (is_.eof()) {
        byte >> low;
        return high;
    }
    is_.get(buffer_);
    char lowbits = buffer_ >> high;
    byte |= lowbits;
    return 8;
}

int alg4::util::StreamBitIn::readBit(bool & bit)
{
   
    if (count_ == 8)
    {
        if (is_.eof())
            return 0;
        is_.get(buffer_);
        count_ = 0;
    }
    bit = buffer_ >> (7 - count_) & 1;
    count_++;
    return 1;
}