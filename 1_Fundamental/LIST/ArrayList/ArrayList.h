#ifndef ARRAYLIST
#define ARRAYLIST

#include <cstddef>
#include "../Utility.h"
#include <utility>

using alg4::copy;
using alg4::Allocator;


namespace alg4
{
    template <typename T, typename Alloc = std::allocator<T>>
    class ArrayList {
    public:
        using value_type = T;
        ArrayList();
        explicit ArrayList(int len, const value_type& val);
        ArrayList(const ArrayList& other);
        ArrayList(ArrayList&& other) noexcept;
        ArrayList& operator=(const ArrayList& other);
        ArrayList& operator=(ArrayList&& other) noexcept;
        ~ArrayList();

        value_type& operator[](const int index)
        {
            if (index < 0 || index >= len())
                throw std::runtime_error("Index Out range!!!");
            return *(begin_ + index);
        }

        void append(const value_type& val);
        void pop_back();
        void insert(size_t index, value_type val);
        // void remove(size_t index);

        size_t len() const { return end_ - begin_; }
        size_t capacity() const { return cap_ - begin_; }
        value_type* cbegin() const { return begin(); }
        value_type* begin() { return begin_; }
        value_type* cend() const { return end(); }
        value_type* end() { return end_; }
        value_type back()
        {
            if (end_ == begin_)
                throw std::runtime_error("The List is empty!!");
            return *(end_ - 1);
        }

    private:
        value_type* begin_;
        value_type* end_;
        value_type* cap_;
        static Alloc alloc_;

        T* allocate(size_t capacity)
        {
            return alloc_.allocate(capacity);
        }

        void deallocate() noexcept
        {
            for (auto desc = end_; desc != begin_;)
                alloc_.destroy(--desc);
            alloc_.deallocate(begin_, capacity());
            begin_ = end_ = cap_ = nullptr;
        }
    
        void reallocate_tool(value_type* newdata, const size_t newlen, const size_t newcapacity)
        {
            begin_ = newdata;
            end_ = begin_ + newlen;
            cap_ = begin_ + newcapacity;
        }
        void copy_tool(const ArrayList& other) noexcept
        {
            begin_ = other.begin_;
            end_ = other.end_;
            cap_ = other.cap_;
        }
    };

    
    template <typename T, typename Alloc>
    Alloc ArrayList<T, Alloc>::alloc_;

    template <typename T, typename Alloc>
    ArrayList<T, Alloc>::ArrayList() : begin_(nullptr), end_(nullptr), cap_(nullptr)
    {
    }

    template <typename T, typename Alloc>
    ArrayList<T, Alloc>::~ArrayList()
    {
        deallocate();
    }

    template <typename T, typename Alloc>
    ArrayList<T, Alloc>::ArrayList(int len, const value_type& val) : begin_(nullptr), end_(nullptr), cap_(nullptr)
    {
        size_t capacity = len == 0 ? 1 : len * 2;
        auto new_data = allocate(capacity);
        reallocate_tool(new_data, len, capacity);
        for (auto i = begin_; i != end_; ++i)
            alloc_.construct(i, val);
    }

    template <typename T, typename Alloc>
    ArrayList<T, Alloc>::ArrayList(const ArrayList& other)
    {
        size_t capacity = other.capacity();
        size_t len = other.len();
        begin_ = allocate(capacity);
        copy(other.cbegin(), other.cend(), begin_);
        end_ = begin_ + len;
        cap_ = begin_ + capacity;
    }

    template <typename T, typename Alloc>
    ArrayList<T, Alloc>::ArrayList(ArrayList&& other) noexcept
    {
        copy_tool(other);
        other.begin_ = other.end_ = other.cap_ = nullptr;
    }
    template <typename T, typename Alloc>
    ArrayList<T, Alloc>& ArrayList<T, Alloc>::operator=(const ArrayList& other)
    {
        if (this != &other) {
            deallocate();
            size_t capacity = other.capacity();
            size_t len = other.len();
            begin_ = allocate(capacity);
            copy(other.cbegin(), other.cend(), begin_);
            reallocate_tool(begin_, len, capacity);
        }
        return *this;
    }

    template <typename T, typename Alloc>
    ArrayList<T, Alloc>& ArrayList<T, Alloc>::operator=(ArrayList&& other) noexcept
    {
        if (this != &other) {
            deallocate();
            copy_tool(other);
            other.begin_ = other.end_ = other.cap_ = nullptr;
        }
        return *this;
    }
    template <typename T, typename Alloc>
    void ArrayList<T, Alloc>::append(const value_type& val)
    {
        insert(len(), val);
    }
    template <typename T, typename Alloc>
    void ArrayList<T, Alloc>::pop_back()
    {
        end_--;
    }

    template<typename T, typename Alloc>
    inline void ArrayList<T, Alloc>::insert(size_t index, value_type val)
    {
        size_t size = len();
        if (index > size || index < 0)
            throw std::runtime_error("Out of range!");
        if (cap_ != end_) {
            auto itr = end_++;
            for (; itr != begin_ + index; itr--)
                *itr = *(itr - 1);
            alloc_.construct(itr, val);
            return;
        }
        size_t newcap = capacity() == 0 ? 1 : capacity() * 2;
        auto newdata = allocate(newcap);
        auto desc = newdata, source = begin_;
        for (;desc != index + newdata;)
            alloc_.construct(desc++, std::move(*source++));
        alloc_.construct(desc++, val);
        for (;desc != newdata + size + 1; )
            alloc_.construct(desc++, std::move(*source++));
        deallocate();
        reallocate_tool(newdata, size + 1, newcap);
    }
}
#endif