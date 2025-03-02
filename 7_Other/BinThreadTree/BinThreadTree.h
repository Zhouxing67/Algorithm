#ifndef BIN_THREAD_TREE_H
#define BIN_THREAD_TREE_H
#include <functional>
#include <iostream>
using std::cout;
using std::function;
namespace alg4
{
    struct Node
    {
        int data_;
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        bool llag = 0;
        bool rlag = 0;
    };
    void in_thread(Node* node, Node* pre);
    void create_thread(Node* root);
    Node* first_Node(Node* node);
    Node* next_Node(Node* node);
    Node* last_Node(Node* node);
    void in_order(Node* node, std::function<void( Node* )> visit);
    void visit(Node* node);
}
#endif