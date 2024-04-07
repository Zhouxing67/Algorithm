#ifndef UTL_INCLUDE
#define UTL_INCLUDE
#include <limits>
#include <iostream>
#include <cstdlib>

namespace alg4
{
template <typename T>
    class Allocator
    {
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using void_pointer = void *;
        using const_void_pointer = const void *;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;

        Allocator() = default;
        ~Allocator()
        {
            //std::cout << "alloc_count_  == " << alloc_count_ << std::endl;
        }

        template <typename U, typename... Args>
        void construct(U *p, Args &&...args)
        {
            new (p) U(std::forward<Args>(args)...);
        }

        template <typename U, typename... Args>
        void destory(U *p)
        {
            p->~U();
        }

        template <typename U>
        struct rebind
        {
            using other = Allocator<U>;
        };

        size_type get_alloc_count_() const
        {
            return alloc_count_;
        }

        pointer allocate(size_type n)
        {
            alloc_count_ += n;
            //std::cout << "Allocator::allocate OBJ Size :" << n << std::endl;
            return static_cast<pointer>(operator new(sizeof(value_type) * n));
        }

        void deallocate(pointer p, size_type objects_num)
        {
            alloc_count_ -= objects_num;
            //std::cout << "Allocator::deallocate :" << objects_num << std::endl;
            if(p != nullptr)
                operator delete (p);
        }

    private:
        size_type alloc_count_;
    };


    template <typename T>
    void copy(T* begin_, T* end_, T* dest_)
    {
        static Allocator<T> alloc;
        for (auto temp = begin_; temp != end_;)
            alloc.construct(dest_++, *temp++);
    }
}
#endif