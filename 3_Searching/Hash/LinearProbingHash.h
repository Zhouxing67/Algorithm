#ifndef LINEARPROBINGHASH_INCLUDE_H
#define LINEARPROBINGHASH_INCLUDE_H
#include "Hash.h"
#include <cstring>

using std::allocator;
namespace alg4::search
{
    template<typename K, typename V>
    class LinearHash : public Hash<K, V>
    {
    public:
        explicit LinearHash()
        {
            data_ = alloc_.allocate(this->M_);
            memset(data_, 0, sizeof(K*) * this->M_);
        }
        ~LinearHash()
        {
            auto cur = data_;
            for (size_t i = 0; i < this->M_; i++) {
                alloc_.destroy(cur);
            }
            alloc_.deallocate(data_, this->M_);
            data_ = nullptr;
        }
        void put(K key, V val) override
        {
            size_t pos = linerProbe(key, this->M_);
            alloc_.construct(data_ + pos, std::make_unique<pair<K, V>>(std::make_pair(key, val)));
            this->N_++;
            check();
        }

        void del(K key)override
        {
            size_t pos = findPos(key);
            if (pos == -1)
                return;
            data_[pos] = nullptr;
            while (data_[++pos] != nullptr) {
                K key = data_[pos]->first;
                V val = data_[pos]->second;
                data_[pos] = nullptr;
                put(key, val);
            }
            this->N_--;
            check();
        }

        unique_ptr<V> get(K key) override
        {
            size_t pos = findPos(key);
            return pos == -1 ? nullptr : std::make_unique<V>(data_[pos]->second);
        }

    private:
        unique_ptr<pair<K, V>>* data_ = nullptr;
        static inline allocator<unique_ptr<pair<K, V>>> alloc_ = allocator<unique_ptr<pair<K, V>>>();

        size_t linerProbe(const K& obj, size_t Size)
        {
            size_t pos = this->hash_(obj) / Size;
            while (data_[pos] != nullptr) {
                pos = (pos + 1) % Size;
            }
            return pos;
        }

        long long findPos(const K& key)
        {
            size_t pos = this->hash_(key) / this->M_;
            while (data_[pos] != nullptr && data_[pos]->first != key)
                pos = (pos + 1) % this->M_;

            if (data_[pos] == nullptr)
                return -1;
            return pos;
        }

        void realloc(size_t newSize)
        {
            auto newdata = alloc_.allocate(newSize);
            memset(newdata, 0, newSize * sizeof(K*)); // 修正memset参数

            auto cur = newdata; // 使用cur指针来迭代新内存位置
            for (size_t i = 0; i < this->M_; i++) {
                if (data_[i] != nullptr) {
                    size_t pos = linerProbe(data_[i]->first, newSize);
                    alloc_.construct(cur + pos, std::make_unique<pair<K, V>>(std::move(*data_[i]))); // 使用cur指针而不是tmp指针
                }
            }
            data_ = newdata;
            this->M_ = newSize;
        }


        void check()
        {
            double ratio = this->N_ / this->M_;
            if (ratio > 1 / 2)
                realloc(this->M_ * 2);
            if (ratio < 1 / 8)
                realloc(this->M_ / 2);
        }


    };

}
#endif