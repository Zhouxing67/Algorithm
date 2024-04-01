#include "func.h"

class RedBlackTree {
public:
    RedBlackTree() :root_ (nullptr), _size(0) {};
    string get(int key) { return get(root_, key); }
    void put(int key, string val)
    {
        root_ = put(root_, key, val);
        root_->color = _black;
    }

private:
    class Node {
    public:
        Node(int key, string val, bool color)
            :key_(key), _val(val), color(color)
        {
            left = nullptr;
            right = nullptr;
        }
        //private:
        int key_;
        string _val;
        Node* left;
        Node* right;
        bool color;
    };
    Node* root_;
    int _size;

    string get(Node*, int);
    Node* put(Node*, int, string);

    Node* rotateRight(Node* h)
    {
        Node* tmp = h->left;
        h->left = tmp->right;
        tmp->right = h;
        tmp->color = h->color;
        h->color = _red;
        return tmp;
    }
    Node* rotateLeft(Node* h)
    {
        Node* tmp = h->right;
        h->right = tmp->left;
        tmp->left = h;
        tmp->color = h->color;
        h->color = _red;
        return tmp;
    }
    void flipColors(Node* h)
    {
        h->color = _red;
        h->left->color = _black;
        h->right->color = _black;
    }
    bool isRed(Node* x)
    {
        if (x == nullptr) return false;
        return x->color == _red;
    }
    int getmin(Node* root)
    {
        int key = -1;
        while (root != nullptr) {
            key = root->key_;
            root = root->left;
        }
        return key;
    }
    int getmax(Node* root)
    {
        int key = -1;
        while (root != nullptr) {
            key = root->key_;
            root = root->right;
        }
        return key;
    }
    void getKeys(Node* root, queue<int>& res)
    {
        //inorder BFS
        if (root == nullptr) return;
        getKeys(root->left, res);
        res.push(root->key_);
        getKeys(root->right, res);
    }
public:
    bool contains(int) { return _size; }
    int getsize() { return _size; }
    int getmin() { return getmin(root_); }
    int getmax() { return getmax(root_); }
    void getKeys(queue<int>& res) { return getKeys(root_, res); }
    int getRoot() { return root_->key_; }
    //each path from root to leaf has the same black number
    bool isBalanced()
    {
        int black = 0;
        Node* root = root_;
        while (root != nullptr) {
            if (!isRed(root)) black++;
            root = root->left;
        }
        return isBalanced(root, black);
    }
    bool isBalanced(Node* root, int numBlack)
    {
        if (root == nullptr)
            return numBlack == 0;
        if (isRed(root))
            numBlack--;
        return isBalanced(root->left, numBlack) && isBalanced(root, numBlack);
    }
protected:
    const bool _red = true;
    const bool _black = false;

};

string RedBlackTree::get(Node* x, int key)
{
    while (x != nullptr) {
        if (x->key_ == key)
            return x->_val;
        else if (x->key_ > key)
            return get(x->left, key);
        else
            return get(x->right, key);
    }
    return nullptr;
}

RedBlackTree::Node* RedBlackTree::put(Node* h, int key, string val)
{
    if (h == nullptr) {
        _size++;
        return new RedBlackTree::Node(key, val, _red);
    }
    if (h->key_ == key) h->_val = val;
    else if (h->key_ > key) h->left = put(h->left, key, val);
    else h->right = put(h->right, key, val);

    //TODO fix-up links
    if (isRed(h->right) && !isRed(h->left))
        h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left))
        h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right))
        flipColors(h);

    return h;
}


