#ifndef CIRQUE_INCLUDE_H
#define CIRQUE_INCLUDE_H
#include <cassert>
#include <vector>
namespace alg4
{
    // Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

// circular q view of std::vector.

    template <typename T>
    class circular_q {
    private:
        size_t max_items_ = 0;
        typename std::vector<T>::size_type head_ = 0;
        typename std::vector<T>::size_type tail_ = 0;
        size_t overrun_counter_ = 0;
        std::vector<T> data_;

        void copy_moveable(circular_q&& other) noexcept
        {
            max_items_ = other.max_items_;
            head_ = other.head_;
            tail_ = other.tail_;
            overrun_counter_ = other.overrun_counter_;
            data_ = std::move(other.data_);

            // put &&other in disabled, but valid state
            other.max_items_ = 0;
            other.head_ = other.tail_ = 0;
            other.overrun_counter_ = 0;
        }

    public:
        using value_type = T;

        // empty ctor - create a disabled queue with no elements allocated at all
        circular_q() = default;

        explicit circular_q(size_t max_items)
            : max_items_(max_items + 1)  // one item is reserved as marker for full q
            ,
            data_(max_items_)
        {}

        circular_q(const circular_q&) = default;
        circular_q& operator=(const circular_q&) = default;

        // move cannot be default,
        // since we need to reset head_, tail_, etc to zero in the moved object
        circular_q(circular_q&& other) noexcept
        {
            copy_moveable(std::move(other));
        }

        circular_q& operator=(circular_q&& other) noexcept
        {
            copy_moveable(std::move(other));
            return *this;
        }

        // push back, overrun (oldest) item if no room left
        void push_back(T&& item)
        {
            if (max_items_ > 0) {
                data_[tail_] = std::move(item);
                tail_ = (tail_ + 1) % max_items_;

                if (tail_ == head_)  // overrun last item if full
                {
                    head_ = (head_ + 1) % max_items_;
                    ++overrun_counter_;
                }
            }
        }

        // Return reference to the front item.
        // If there are no elements in the container, the behavior is undefined.
        const T& front() const { return data_[head_]; }

        T& front() { return data_[head_]; }

        // Return number of elements actually stored
        size_t size() const
        {
            return tail_ >= head_ ? tail_ - head_ : max_items_ - (head_ - tail_);
        }

        // Return const reference to item by index.
        // If index is out of range 0…size()-1, the behavior is undefined.
        const T& at(size_t i) const
        {
            assert(i < size());
            return data_[(head_ + i) % max_items_];
        }

        // Pop item from front.
        // If there are no elements in the container, the behavior is undefined.
        void pop_front() { head_ = (head_ + 1) % max_items_; }

        bool empty() const { return tail_ == head_; }

        bool full() const
        {
            // head is ahead of the tail by 1
            if (max_items_ > 0) {
                return ((tail_ + 1) % max_items_) == head_;
            }
            return false;
        }

        size_t overrun_counter() const { return overrun_counter_; }

        void reset_overrun_counter() { overrun_counter_ = 0; }

        // copy from other&& and reset it to disabled state
       
    };
}
#endif