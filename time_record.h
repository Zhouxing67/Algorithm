#ifndef TIME_COUNT_INCLUDE
#define TIME_COUNT_INCLUDE
#include <chrono>
#include <iostream>
#include <iomanip>

using std::chrono::steady_clock;
using std::chrono::seconds;
using std::chrono::duration_cast;
using std::endl;
using std::cout;

namespace alg4::util
{
    class time_recorder {
    private:
        static steady_clock init_;
        std::chrono::time_point<steady_clock> begin_;
        bool diff_n_ = 0;
    public:

        explicit time_recorder() : begin_(init_.now())
        {
        }

        ~time_recorder()
        {
            if (!diff_n_) {
                auto time_diff = diff();
                cout << "cost time: " << std::setw(8) << std::left<< time_diff.count() << "milliseconds  ";
            }
        }
        time_recorder(const time_recorder& other) = delete;
        time_recorder& operator=(const time_recorder& other) = delete;

        std::chrono::milliseconds diff()
        {
            diff_n_ = 1;
            return duration_cast<seconds>(init_.now() - begin_);
        }
    };

    steady_clock time_recorder::init_;
}
#endif  