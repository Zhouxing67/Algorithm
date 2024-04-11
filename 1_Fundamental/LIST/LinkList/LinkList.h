#ifndef LINKLIST
#define LINKLIST
#include <functional>
#include "../Utility.h"
#include <string>
#include <cassert>

using alg4::list::Allocator;
using std::function;


namespace alg4::List
{

    template <typename T, typename Alloc = Allocator<T>>
    class LinkList
    {
    public:
        LinkList();
        ~LinkList();
        LinkList(const LinkList& other);
        LinkList(LinkList&& other) noexcept;
        LinkList& operator=(const LinkList& other);
        LinkList& operator=(LinkList&& other) noexcept;
        void insert(const T& value, const int pos);
        void append(const T& value);
        void remove(const int pos);
        void pop_back();
        void pop_front();
        T& operator[](const int pos);
        T at(const int pos);
        int len() const { return len_; }

    private:
        struct Node
        {
            T data_;
            Node* next_;

            Node(const T& value) : data_(value), next_(nullptr) {}
            Node() : next_(nullptr) {}
            Node(const Node& other) = delete;
            Node& operator=(const Node& other) = delete;
            ~Node()
            {
                next_ = nullptr;
            }
        };

        typedef typename Alloc::template rebind<LinkList<T, Alloc>::Node>::other Node_alloc;

        Node* dumyHead_;
        Node* cur_;
        int len_;

        static Node_alloc alloc_;

        void free()
        {
            cur_ = dumyHead_;
            while (cur_ != nullptr) {
                LinkList<T, Alloc>::Node* next = cur_->next_;
                alloc_.destory(cur_);
                alloc_.deallocate(cur_, 1);
                cur_ = next;
            }
        }
       
        void move_pos(const int pos)
        {
            cur_ = dumyHead_;
            for (int i = -1;i < pos;++i)
                cur_ = cur_->next_;
        }

        void copy_tools(const LinkList& other)
        {
            auto other_cur = other.dumyHead_;
            dumyHead_ = alloc_.allocate(1);
            cur_ = dumyHead_;
            while (other_cur->next_ != nullptr) {
                alloc_.construct(cur_, other_cur->data_);
                cur_->next_ = alloc_.allocate(1);
                other_cur = other_cur->next_;
                cur_ = cur_->next_;
            }
            alloc_.construct(cur_, other_cur->data_);
            len_ = other.len_;
        }
        void move_tools(LinkList&& other) noexcept
        {
            cur_ = other.cur_;
            len_ = other.len_;
            dumyHead_ = other.dumyHead_;
            other.dumyHead_ = other.len_ = other.cur_ = nullptr;
        }
    };

    template <typename T, typename Alloc>
    typename LinkList<T, Alloc>::Node_alloc LinkList<T, Alloc>::alloc_;

    template <typename T, typename Alloc>
    LinkList<T, Alloc>::LinkList() : cur_(nullptr), len_(0)
    {
        dumyHead_ = alloc_.allocate(1);
        alloc_.construct(dumyHead_);
    }

    template <typename T, typename Alloc>
    LinkList<T, Alloc>::~LinkList()
    {
        free();
    }

    template <typename T, typename Alloc>
    LinkList<T, Alloc>::LinkList(const LinkList& other)
    {
        copy_tools(other);
    }

    template<typename T, typename Alloc>
    LinkList<T, Alloc>& LinkList<T, Alloc>::operator=(const LinkList& other)
    {
        if (&other != this) {
            free();
            copy_tools(other);
        }
        return *this;
    }
    template<typename T, typename Alloc>
    LinkList<T, Alloc>::LinkList(LinkList&& other) noexcept
    {
        move_tools(std::move(other));
    }
    template<typename T, typename Alloc>
    LinkList<T, Alloc>& LinkList<T, Alloc>::operator=(LinkList&& other) noexcept
    {
        free();
        move_tools(std::move(other));
    }

    template<typename T, typename Alloc>
    void LinkList<T, Alloc>::insert(const T& value, const int pos)
    {
        if (pos > len() || pos < 0)
            throw std::runtime_error("Invalid pos");
        move_pos(pos - 1);
        auto newdata = alloc_.allocate(1);
        alloc_.construct(newdata, value);
        newdata->next_ = cur_->next_;
        cur_->next_ = newdata;
        len_++;
    }
    template<typename T, typename Alloc>
    void LinkList<T, Alloc>::append(const T& value)
    {
        insert(value, len());
    }
    template<typename T, typename Alloc>

    void LinkList<T, Alloc>::remove(const int pos)
    {
        if (pos > len() - 1 || pos < 0)
            throw std::runtime_error("Invalid pos");
        move_pos(pos - 1);
        auto temp = cur_->next_;
        cur_->next_ = cur_->next_->next_;
        len_--;
        alloc_.destory(temp);
        alloc_.deallocate(temp, 1);
    }
    template<typename T, typename Alloc>
    void LinkList< T, Alloc>::pop_front()
    {
        remove(0);
    }

    template<typename T, typename Alloc>
    void LinkList< T, Alloc>::pop_back()
    {
        remove(len() - 1);
    }

    template<typename T, typename Alloc>
    T& LinkList<T, Alloc>::operator[](const int pos)
    {
        if (pos > len() - 1 || pos < 0)
            throw std::runtime_error("Invalid pos");
        move_pos(pos);
        return cur_->data_;
    }

    template<typename T, typename Alloc>
    T LinkList<T, Alloc>::at(const int pos)
    {
        if (pos > len() - 1 || pos < 0)
            throw std::runtime_error("Invalid pos");
        move_pos(pos);
        return cur_->data_;
    }
}
#endif