#ifndef UNIQUEPTR
#define UNIQUEPTR
#include "deleter.h"
template <typename ValueType, typename deleter = DefaultDeleter<ValueType>>
class uniqueptr
{
private:
    ValueType *data;
    deleter del;

public:
    uniqueptr(deleter d = deleter()) : data(nullptr), del(d) {}
    uniqueptr (const uniqueptr &other) = delete;
    uniqueptr &operator=(const uniqueptr &other) = delete;
    explicit uniqueptr(ValueType *ptr, deleter d = deleter())
    {
        data = ptr;
        del = d;
    }
    uniqueptr (uniqueptr &&other) noexcept
    {
        data = other.data;
        del = std::move(other.del);
        other.data = nullptr;
    }
    uniqueptr &operator=(uniqueptr &&other) noexcept
    {
        del(data);
        data = other.data;
        del = std::move(other.del);
        other.data = nullptr;
        return *this;
    }
    void reset(ValueType *ptr, deleter d = deleter())
    {
        del(data);
        data = ptr;
        del = std::move(d);
    }
    ValueType *release()
    {
        auto val = data;
        data = nullptr;
        return std::move(val);
    }
    
    ValueType& operator* () { return *data; }

    ~uniqueptr() 
    { 
        del(data); 
    }
};

#endif