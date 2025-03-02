#include "BinThreadTree.h"

using alg4::Node;

void alg4::in_thread(Node* node, Node* pre)
{
    if (node == nullptr)
        return;
    in_thread(node->left_, pre);

    //左链接指向前驱
    if (node->left_ == nullptr) {
        node->left_ = pre;
        node->llag = 1;
    }
    //右链接指向后继
    if (pre != nullptr && pre->right_ == nullptr) {
        pre->right_ = node;
        pre->rlag = 1;
    }

    in_thread(node->right_, pre);
}

void alg4::create_thread(Node* root)
{
    if (root == nullptr)
        return;
    Node* pre = nullptr;
    in_thread(root, pre);
    //处理最后一个节点
    pre->right_ = nullptr;
    pre->rlag = 1;
}
//以node为根节点的子树的第一个节点
Node* alg4::first_Node(Node* node)
{
    while (node->llag == 0)
        node = node->left_;
    return node;
}

//获取node的后继
Node* alg4::next_Node(Node* node)
{
    //当前节点右链接不是后继的话，以它右孩子为根的子树的第一个节点就是后继，这是由中序遍历的性质得到的
    if (node->rlag == 0)
        return first_Node(node->right_);
    return
        node->right_;
}

void alg4::in_order(Node* node, std::function<void(Node*)> visit)
{
    for (Node* p = first_Node(node); node != nullptr; p = next_Node(p))
        visit(p);
}

void alg4::visit(Node* node) { std::cout << node->data_ << std::endl; }