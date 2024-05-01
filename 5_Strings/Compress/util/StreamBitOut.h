#ifndef STREAM_BIT_OUT_H
#define STREAM_BIT_OUT_H
#include <iostream>

#include <vector>
using std::vector;
using std::ostream;


namespace alg4::util
{
    class StreamBitOut {
    private:
        ostream& os_;
        char byte_ = 0;
        size_t count_ = 0;

    public:
        StreamBitOut(ostream& os) : os_(os) { }
        ~StreamBitOut()
        {
            close();
        }
        void close(){flush();}

        void writeOneBit(bool bit);
        void writeOneByte(char byte);
        void flush();
    };
}
#endif