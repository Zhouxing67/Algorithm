#ifndef NODE_H
#define NODE_H

namespace alg4::str
{
    struct Node
    {
        char chr_ = '\0';
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        int freq_ = 0;//解码时无用

        //枝节点初始化
        Node(Node* left, Node* right, int freq)
            : left_(left), right_(right), freq_(freq)
        { }

        //叶节点初始化
        Node(char chr, int freq) : chr_(chr), freq_(freq)
        {}

        bool operator< (Node* other)
        {
            return freq_ < other->freq_;
        }


        bool isleaf()
        {
            return left_ == nullptr && right_ == nullptr;
        }

        ~Node()
        {
            delete left_;
            delete right_;
            left_ = nullptr;
            right_ = nullptr;
        }
    };

    /* Node* root_ = nullptr; */
}
#endif