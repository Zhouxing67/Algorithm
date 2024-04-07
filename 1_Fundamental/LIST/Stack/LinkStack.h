#ifndef LINKSTACK_INCLUDE_H
#define LINKSTACK_INCLUDE_H
#include <memory>

namespace alg4
{
    template<typename T, typename alloc = std::allocator<T>>
    class LinkStack {
    private:
        struct Node
        {
            T data_;
            Node* next_;

            Node(const T &value) : data_(value), next_(nullptr) {}
            Node() : next_(nullptr) {}
            Node(const Node& other) = delete;
            Node& operator=(const Node& other) = delete;
            ~Node()
            {
                next_ = nullptr;
            }
        };
        typedef typename std::allocator_traits<alloc>::template rebind_alloc<typename LinkStack<T, alloc>::Node> Node_alloc;

        Node* top_;
        static Node_alloc alloc_;

    public:
        LinkStack() : top_(alloc_.allocate(1))
        {
            alloc_.construct(top_, 0);
        }

        ~LinkStack()
        {
            while (top_ != nullptr) {
                auto next = top_->next_;
                alloc_.destroy(top_);
                alloc_.deallocate(top_, 1);
                top_ = next;
            }
        }

        bool empty() { return top_->next_ == nullptr; }

        void pop()
        {
            if (empty())
                throw std::runtime_error("Pop on the empty stack");
            auto next = top_->next_;
            top_->next_ = next->next_;
            alloc_.destroy(next);
            alloc_.deallocate(next, 1);
        }

        T top()
        {
            if (empty()) 
                throw std::runtime_error("Empty Stack");
            return top_->next_->data_;

        }

        void push(const T& val)
        {
            Node* newdata = alloc_.allocate(1);
            alloc_.construct(newdata, val);
            newdata->next_ = top_->next_;
            top_->next_ = newdata;
        }
    };

    template<typename T, typename alloc>
    typename LinkStack<T, alloc>::Node_alloc LinkStack<T, alloc>::alloc_;
}

#endif