#include "StreamBitOut.h"

void alg4::util::StreamBitOut::writeOneBit(bool bit)
{
    if (count_ == 8)
        flush();
    if (bit)
        byte_ |= (1 << (7 - count_));
    count_++;
}

void alg4::util::StreamBitOut::writeOneByte(char byte)
{
    int high = 8 - count_, low = count_;
    byte_ |= byte >> low;
    count_ = 8;
    flush();
    byte_ = byte << high;
    count_ = low;
}

void alg4::util::StreamBitOut::flush()
{
    if (count_ > 0) {
        os_.put(byte_);
        byte_ = 0;
        count_ = 0;
        std::cout << "flush!!!" << std::endl;
    }
}