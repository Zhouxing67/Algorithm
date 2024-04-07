#ifndef LINKQUE_INCLUDE_H
#define LINKQUE_INCLUDE_H

#include<memory>
namespace alg4
{
    template<typename T, typename alloc = std::allocator<T>>
    class LinkQue {
    private:
        struct Node
        {
            T data_;
            Node* next_ = nullptr;

            Node() = default;
            Node(const T& value) : data_(value), next_(nullptr) {}
            Node(const Node& other) = delete;
            Node& operator=(const Node& other) = delete;
            ~Node()
            {
                next_ = nullptr;
            }
        };

        typedef typename std::allocator_traits<alloc>::template rebind_alloc<typename LinkQue<T, alloc>::Node> Node_alloc;
        Node* front_;
        Node* aft_;
        static Node_alloc alloc_;
    public:

        LinkQue()
        {
            front_ = alloc_.allocate(1);
            alloc_.construct(front_);

            aft_ = front_;
        }

        bool empty() { return aft_ == front_; }

        T front()
        {
            if (empty())
                throw std::runtime_error("The queue is emty");
            /* code */
            return front_->next_->data_;
        }

        void push(const T& val)
        {
            auto newdata = alloc_.allocate(1);
            alloc_.construct(newdata, val);
            aft_->next_ = newdata;
            aft_ = newdata;
        }

        void pop()
        {
            if (empty())
                throw std::runtime_error("Pop on the empty queue");
            auto next = front_->next_;
            front_->next_ = next->next_;
            alloc_.destroy(next);
            alloc_.deallocate(next, 1);
            if (front_->next_ == nullptr)
                aft_ = front_;
        }
    };
    template<typename T, typename alloc>
    typename LinkQue<T, alloc>::Node_alloc LinkQue<T, alloc>::alloc_;
}
#endif