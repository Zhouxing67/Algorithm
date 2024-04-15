#ifndef NODE_INCLUDE_H
#define NODE_INCLUDE_H

namespace alg4::binaryTree
{
    struct Node
    {
        int val_;
        Node* left_;
        Node* right_;

        Node(int val) : val_(val), left_(nullptr), right_(nullptr) {}

        ~Node()
        {
            left_ = nullptr;
            right_ = nullptr;
        }
    };

    Node* init_tree()
    {
        Node* root = new Node(0);
        root->left_ = new Node(1);
        root->left_->left_ = new Node(3);
        root->left_->right_ = new Node(4);
        root->left_->right_->left_ = new Node(5);
        
        root->right_ = new Node(2);
        root->right_->left_ = new Node(6);
        root->right_->right_ = new Node(7);
        root->right_->right_->right_ = new Node(8);
        return root;
    }

    void delete_tree(Node* root)
    {
        if (root == nullptr)
            return;
        delete_tree(root->left_);
        delete_tree(root->right_);
        delete root;
    }
}
#endif