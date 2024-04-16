#ifndef BST_INCLUDE_H
#define BST_INCLUDE_H
#include <memory>
namespace alg4::search
{
    template<typename K, typename V, typename Comp = std::less<K>>
    class BST {
    public:
        explicit BST() = default;
        ~BST()
        {
            clear(root_);
        }

        size_t size() { return size(root_); }
        void update(K key, V val) { root_ = update(root_, key, val); }

        std::unique_ptr<V> find(K key)
        {
            Node* node = find(root_, key);
            if (node == nullptr)
                return nullptr;
            return std::make_unique<V>(node->val_);
        }
        std::unique_ptr<K> min()
        {
            if (root_ == nullptr)
                return nullptr;
            Node* minNode = min(root_);
            return std::make_unique<K>(minNode->key_);
        }
        std::unique_ptr<K> floor(K key)
        {
            Node* floorNode = floor(root_, key);
            if (floorNode == nullptr)
                return nullptr;
            return std::make_unique<K>(floorNode->key_);
        }
        std::unique_ptr<K> select(size_t rank)
        {
            Node* node = select(root_, rank);
            if (node == nullptr)
                return nullptr;
            return std::make_unique<K>(node->key_);
        }
        size_t rank(K key)
        {
            return rank(root_, key);
        }
        void deleteMin()
        {
            if (root_ == nullptr)
                return;
            root_ = deleteMin(root_);
        }
        void deleteKey(K key)
        {
            root_ = deleteKey(root_, key);
        }
    private:
        struct Node
        {
            K key_;
            V  val_;
            Node* left_;
            Node* right_;
            size_t N;

            Node(K key, V val) :
                key_(key), val_(val), left_(nullptr), right_(nullptr), N(1)
            { }
            ~Node()
            {
                left_ = nullptr;
                right_ = nullptr;
            }
        };
        Node* root_ = nullptr;
        static Comp comparef;
        //后序遍历释放内存
        void clear(Node* node)
        {
            if (node == nullptr)
                return;
            clear(node->left_);
            clear(node->right_);
            delete node;
            node = nullptr;
        }
        size_t size(Node* node)
        {
            if (node == nullptr)
                return 0;
            return node->N;
        }
        Node* update(Node* node, K key, V val)
        {
            if (node == nullptr)
                return new Node(key, val);
            if (node->key_ == key)
                node->val_ = val;
            else if (comparef(key, node->key_))
                node->left_ = update(node->left_, key, val);
            else
                node->right_ = update(node->right_, key, val);

            node->N = size(node->left_) + size(node->right_) + 1;
            return node;
        }
        Node* find(Node* node, K key)
        {
            Node* res = nullptr;
            if (node == nullptr || node->key_ == key)
                res = node;
            else if (comparef(key, node->key_))
                res = find(node->left_, key);
            else
                res = find(node->right_, key);
            return res;
        }
        Node* min(Node* node)
        {
            while (node->left_ != nullptr)
                node = node->left_;
            return node;
        }
        Node* floor(Node* node, K key)
        {
            if (node == nullptr)
                return nullptr;

            if (node->key_ == key)
                return node;
            else if (comparef(key, node->key_))
                return floor(node->left_, key);
            else {
                Node* tmp = floor(node->right_, key);
                if (tmp != nullptr)
                    return node = tmp;
            }
            return node;
        }
        Node* select(Node* node, size_t rank)
        {
            if (node == nullptr)
                return nullptr;
            //左子树的节点总数
            size_t leftSize = size(node->left_);
            if (rank < leftSize)
                return select(node->left_, rank);
            if (rank > leftSize)
                return select(node->right_, rank - 1 - leftSize);
            return node;
        }
        size_t rank(Node* node, K key)
        {
            if (node == nullptr)
                return 0;
            size_t leftSize = size(node->left_);
            if (key == node->key_)
                return leftSize;
            if (key < node->key_)
                return rank(node->left_, key);
            return rank(node->right_, key) + leftSize + 1;

        }
        //isErase 决定是释放内存还是仅丢弃链接
        Node* deleteMin(Node* node, bool isErase = true)
        {
            if (node->left_ == nullptr) {
                Node* newNode = node->right_;
                if(isErase)
                    delete node;
                return newNode;
            }
            node->left_ = deleteMin(node->left_, isErase);
            node->N = 1 + size(node->left_) + size(node->right_);
            return node;
        }
        Node* deleteKey(Node* node, K key)
        {
            if (node == nullptr)
                return nullptr;
            if (key == node->key_) {
                Node* left = node->left_, *right = node->right_;
                if (left == nullptr) {
                    delete node;
                    return right;
                }
                if (right == nullptr) {
                    delete node;
                    return left;
                }
                Node* tmp = node, *minNode;

                node = min(node->right_);
                node->right_ = deleteMin(right, false);
                node->left_ = left;

                delete tmp;
            }
            else if (comparef(key, node->key_))
                node->left_ = deleteKey(node->left_, key);
            else
                node->right_ = deleteKey(node->right_, key);
            node->N = 1 + size(node->left_) + size(node->right_);
            return node;
        }
    };

    template<typename K, typename V, typename Comp>
    Comp BST<K, V, Comp>::comparef;
}
#endif