#include "deleter.h"

template <typename ValueType, typename deleter = DefaultDeleter<ValueType>>
class shareptr
{
private:
    ValueType *data;
    int *counter;
    deleter del;

    // free memory;
    void free()
    {
        if (counter && --(*counter) == 0)
        {
            del(data);
            delete counter;
        }
    }

public:
    shareptr(deleter d = deleter()): data(nullptr), counter(nullptr), del(d) {}
    explicit shareptr(ValueType *p, deleter deler = deleter())
     : data(p), counter(new int(1)), del(deler)
    {}

    shareptr(const shareptr &shptr);
    shareptr &operator= (const shareptr &shptr);

    ~shareptr() { free(); }
    ValueType &operator* (){ return *data; }
    ValueType *get_ptr() { return *data; }
    void displayTimes() { std::cout << *counter << std::endl; }
    //void reset();
};

template <typename ValueType, typename deleter>
shareptr<ValueType, deleter>::shareptr(const shareptr &shptr)
{
    if (shptr.counter)
        ++*shptr.counter;
    data = shptr.data;
    del = shptr.del;
    counter = shptr.counter
}

template <typename ValueType, typename deleter>
shareptr<ValueType, deleter> &shareptr<ValueType, deleter>::operator=(const shareptr &shptr)
{
    if (shptr.counter)
        ++*shptr.counter;
    free();
    data = shptr.data;
    counter = shptr.counter;
    return *this;
}