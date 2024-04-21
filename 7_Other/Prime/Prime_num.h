#ifndef PRIME_NUM_INCLUDE
#define PRIME_NUM_INCLUDE
#include "../../base_include.h"
namespace alg4
{
    //欧拉筛
    //让每一个合数被其最小质因数筛到。


    class Prime_num {
    private:
        vector<int> primes_;
        vector<bool> is_not_primer_;
    public:
        explicit Prime_num(size_t n) :
            is_not_primer_(n + 1)
        {
            for (int i = 2; i <= n; i++) {
                if (!is_not_primer_[i])
                    primes_.push_back(i);
                for (const auto& prime : primes_) {
                    int num = prime * i;
                    if (num > n)
                        break;
                    is_not_primer_[num] = true;
                    if (i % prime == 0)
                        break;
                }
            }
        }

        Prime_num(const Prime_num& other) = delete;

        Prime_num& operator= (const Prime_num& other) = delete;

        bool is_primer(size_t num)
        {
            if (num >= is_not_primer_.size())
                throw std::runtime_error("Out of range");
            return !is_not_primer_[num];
        }

        vector<int> get_primers()
        {
            return primes_;
        }
    };
}
#endif