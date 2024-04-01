#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include"func.h"
/*
key_: Int
val_: string
*/

class BST {
private:
    class Node {
    public:
        int key_;
        string val_;
        int size_;
        Node* left_;
        Node* right_;
        Node(int k, string v, int s) :key_(k), val_(v), size_(s)
        {
            left_ = nullptr;
            right_ = nullptr;
        }
    };
    Node* root;
public:
    BST() { root = nullptr; }
    int sizeTree(Node* root)
    {
        return root == nullptr ? 0 : root->size_;
    }
    int sizeTree() { return sizeTree(root); }
    bool isEmpty() { return sizeTree() == 0; }
    bool contains(int key_) { return get(key_) != ""; }
    string get(int key_) { return get(root, key_); }
    string get(Node* root, int key)
    {
        if (root->key_ == key)
            return root->val_;
        else if (root->key_ > key)
            return get(root->left_, key);
        else
            return get(root->right_, key);
    }
    //插入新元素 或者 更新val
    void put(int key_, string val_)
    {
        //        cout<<key_<<" "<<val_<<endl;
        root = put(root, key_, val_);
    }
    Node* put(Node* root, int key_, string val_)
    {
        if (root == nullptr)
            return new Node(key_, val_, 1);
        if (root->key_ == key_)
            root->val_ = val_;
        else if (root->key_ > key_)
            root->left_ = put(root->left_, key_, val_);
        else
            root->right_ = put(root->right_, key_, val_);

        root->size_ = 1 + sizeTree(root->left_) + sizeTree(root->right_);
        return root;
    }
    //删除极小值
    void deleteMin() { root = deleteMin(root); }
    Node* deleteMin(Node* root)
    {
        if (root->left_ == nullptr) return root->right_;    //删除根节点
        root->left_ = deleteMin(root->left_);
        root->size_ = sizeTree(root->left_) + sizeTree(root->right_);
        return root;
    }
    //删除
    void deleteKey(int key_) { root = deleteKey(root, key_); }
    Node* deleteKey(Node* root, int key_)
    {
        if (root->key_ > key_)
            root->left_ = deleteKey(root->left_, key_);
        else if (root->key_ < key_)
            root->right_ = deleteKey(root->right_, key_);
        else {
            if (root->right_ == nullptr) return root->left_;
            if (root->left_ == nullptr) return root->right_;
            //待删除节点 左右子树均不为空
            //右子树最小节点替换待删除节点
            Node* tmp = root;
            root = minLeaf(root->right_);    //右子树最小节点
            root->right_ = deleteMin(tmp->right_);
            root->left_ = tmp->left_;
        }
    }
    //寻找最小leaf
    Node* minLeaf(Node* root)
    {
        if (root->left_ == nullptr) return root;
        else return minLeaf(root->left_);
    }
    vector<int> print()
    {
        vector<int> BFS;
        queue<Node*> pq;
        pq.push(root);
        while (!pq.empty()) {
            Node* tmp = pq.front();
            pq.pop();
            BFS.push_back(tmp->key_);
            if (tmp->left_ != nullptr)
                pq.push(tmp->left_);
            if (tmp->right_ != nullptr)
                pq.push(tmp->right_);
        }
        return BFS;
    }

};


#endif // BINARYSEARCHTREE_H_INCLUDED
