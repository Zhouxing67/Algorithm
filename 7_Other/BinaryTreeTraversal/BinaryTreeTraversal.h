#ifndef TRAVERSAL_INCLUDE_H
#define TRAVERSAL_INCLUDE_H
#include <functional>
#include <iostream>
#include "Node.h"
#include <stack>

using std::stack;
using std::cout;
using std::endl;
namespace alg4::binaryTree
{
    using visitFunc = std::function<void(Node*&)>;

    visitFunc baseVisit = [](Node*& node) {
        cout << node->val_ << " ";
        };


    class Base_traversal {
    protected:
        visitFunc visit_;
        Node* root_;

        virtual void pre_order(Node* root) = 0;
        virtual void in_order(Node* root) = 0;
        virtual void aft_order(Node* root) = 0;
    public:
        explicit Base_traversal(Node* root, visitFunc visit = baseVisit) : root_(root), visit_(visit) {}

        void pre_order() { pre_order(root_); }
        void in_order() { in_order(root_); }
        void aft_order() { aft_order(root_); }
    };

    class Recursive_traversal : public Base_traversal {
    public:
        Recursive_traversal(Node* root, visitFunc visit = baseVisit) : Base_traversal(root, visit) {}
    private:
        void pre_order(Node* root) override
        {
            if (root == nullptr)
                return;
            visit_(root);
            pre_order(root->left_);
            pre_order(root->right_);
        }

        void in_order(Node* root) override
        {
            if (root == nullptr)
                return;
            in_order(root->left_);
            visit_(root);
            in_order(root->right_);
        }

        void aft_order(Node* root) override
        {
            if (root == nullptr)
                return;
            aft_order(root->left_);
            aft_order(root->right_);
            visit_(root);
        }
    };

    class Iterable_traversal : public Base_traversal {
    public:
        Iterable_traversal(Node* root, visitFunc visit = baseVisit) : Base_traversal(root, visit) {}
    private:
        void pre_order(Node* root) override
        {
            if (root == nullptr)
                return;

            stack<Node*> nodes;
            nodes.push(root);

            while (!nodes.empty()) {
                //前序遍历， 第一次入栈的时候访问；
                Node* current = nodes.top();
                nodes.pop();
                visit_(current);
                if (current->right_)
                    nodes.push(current->right_);
                if (current->left_)
                    nodes.push(current->left_);
            }
        }

        void in_order(Node* root) override
        {
            if (root == nullptr)
                return;

            stack<Node*> nodes;
            Node* current = root;

            while (current != nullptr || !nodes.empty()) {
                while (current != nullptr) {
                    nodes.push(current);
                    current = current->left_;
                }

                current = nodes.top();
                nodes.pop();
                visit_(current);
                current = current->right_;
            }
        }

        void aft_order(Node* root) override
        {
            if (root == nullptr)
                return;

            stack <Node*> nodes;
            Node* last_visited = nullptr, * current = root;

            while (current != nullptr || !nodes.empty()) {
                while (current != nullptr) {
                    nodes.push(current);
                    current = current->left_;
                }

                current = nodes.top();
                if (current->right_ == nullptr || last_visited == current->right_) {
                    visit_(current);
                    nodes.pop();
                    //设置last_visited 与current，避免访问空栈的栈顶
                    last_visited = current;
                    current = nullptr;
                }
                else {
                    current = current->right_;
                }
            }
        }

    };
}
#endif 