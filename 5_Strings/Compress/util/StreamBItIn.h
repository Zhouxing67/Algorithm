#ifndef STREAM_BIT_IN_H
#define STREAM_BIT_IN_H
#include <istream>
#include <vector>

using std::istream;
using std::vector;
namespace alg4::util
{
    class StreamBitIn {
    private:
        istream& is_;
        char buffer_;
        size_t count_ = 0;
    public:
        StreamBitIn(istream& is) : is_(is), buffer_(0)
        {
            if (is_.eof())
                throw std::runtime_error("Stream error!!!");
            is_.get(buffer_);
        }

        int readByte(char & byte);
        int readBit(bool & bit);
    };
}
#endif