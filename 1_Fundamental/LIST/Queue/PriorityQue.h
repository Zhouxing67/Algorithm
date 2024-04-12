#ifndef PRIORITY_INCLUDE_H
#define PRIORITY_INCLUDE_H
#include"../../../alg4def.h"


namespace alg4::list
{
    template<typename T>
    class PriortyQue {
    private:
        T* data_;
        size_t maxSize_ = 0;
        size_t size_ = 0;
        comparableFunc<T> comp_;

        static void sink(size_t k)
        {
            while (k * 2 <= maxSize_) {
                size_t j = 2 * k;
                if (j < maxSize_ && comp_(data_[j], data_[j + 1]))
                    j++;
                if (!comp_(data_[k], data_[j]))
                    return;
                std::swap(data_[k], data_[j]);
                k = j;
            }
        }

        static void swim(size_t k)
        {
            while (k > 1 && comp_(data_[k / 2], data_[k])) {
                std::swap(data_[k / 2], data_[k]);
                k /= 2;
            }
        }

    public:
        explicit PriortyQue(size_t len, comparableFunc<T> comp = std::less<T>())
            : maxSize_(len), data_(new T[len + 1]), comp_(comp)
        {}

        ~PriortyQue()
        {
            delete[] data_;
        }

        T front()
        {
            if (empty())
                throw std::runtime_error("Empty Que");
            return data_[1];
        }
        void pop()
        {
            if (empty())
                throw std::runtime_error("Empty Que");
            std::swap(data_[1], data_[size_]);
            sink(data_, --size_, 1, comp_);
        }

        void push(const T& val)
        {
            if (full())
                throw std::runtime_error("Full Que");
            data_[++size_] = val;
            swim(data_, size_, comp_);
        }

        bool empty()
        {
            return size_ == 0;
        }

        bool full()
        {
            return size_ == maxSize_;
        }

        size_t maxSize_() const
        {
            return size_;
        }
    };

}
#endif