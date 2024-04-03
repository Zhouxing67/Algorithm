#ifndef BITTREE
#define BITTREE

#include <vector>

namespace alg4
{
    class BitTree {

    private:
        std::vector<int> data_;
        int lowbit(int a) { return a & -a; }
    public:
        BitTree(int size)
        {
            data_.resize(size + 1);
        }

        void update(int pos, int val)
        {
            while (pos < data_.size()) {
                data_[pos] += val;
                pos += lowbit(pos);
            }
        }

        int query(int pos)
        {

            int res = 0;
            while (pos) {
                res += data_[pos];
                pos -= lowbit(pos);
            }
            return res;
        }
    };
}
#endif