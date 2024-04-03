#ifndef STACK
#define STACK
#include "ArrayList.h"
#include "LinkList.h"

namespace alg4
{
    template<typename T, typename Container = ArrayList<T>>
    class Stack {
    public:
        Stack() :data_(Container()) {}

        void pop() { data_.pop_back(); }
        void push(const T& val) { data_.append(val); }
        T& top() { return data_[len() - 1]; }
        bool empty() { return len() == 0; }
        int len() { return data_.len(); }
    private:
        Container data_;
    };
}

#endif