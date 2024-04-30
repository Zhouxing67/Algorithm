#ifndef BIT_WRITE_H
#define BIT_WRITE_H
#include <iostream>

#include <vector>
using std::vector;
using std::ostream;


namespace alg4::util
{
    class BitWrite {
    private:
        ostream& os_;
        char byte_ = 0;
        size_t count_ = 0;

    public:
        BitWrite(ostream& os) : os_(os) { }
        ~BitWrite()
        {
            flush();
        }

        ostream& outfile() { return os_; }
        void writeOneBit(bool bit)
        {
            if (count_ == 8)
                flush();
            if (bit)
                byte_ |= (1 << (7 - count_));
            count_++;
        }

        void flush()
        {
            if (count_ > 0)
            {
                os_.put(byte_);
                byte_ = 0;
                count_ = 0;
            }
        }
    };
}
#endif