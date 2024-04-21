#ifndef RBT_INCLUDE_H
#define RBT_INCLUDE_H
#include <memory>
namespace alg4::search
{
    template<typename K, typename V, typename Comp = std::less<K>>
    class RBT {
    public:
        RBT() = default;
        ~RBT()
        {
            clear(root_);
            root_ == nullptr;
        }
        size_t size() { return size(root_); }
        void put(K key, V val)
        {
            root_ = put(root_, key, val);
            root_->col_ = Color::BLACK;
        }
        std::unique_ptr<V> find(K key)
        {
            Node* node = find(root_, key);
            if (node == nullptr) return nullptr;
            return std::make_unique<V>(node->val_);
        }
    private:
        enum class Color {
            RED = true,
            BLACK = false
        };

        struct Node
        {
            K key_;
            V val_;
            Color col_ = Color::BLACK;
            size_t N_ = 1;

            Node* left_ = nullptr;
            Node* right_ = nullptr;

            Node(K key, V val, Color col) :key_(key), val_(val), col_(col)
            { }
            ~Node()
            {
                left_ = nullptr;
                right_ = nullptr;
            }
        };

        void clear(Node* node)
        {
            if (node == nullptr)
                return;
            clear(node->left_);
            clear(node->right_);
            delete node;
            node = nullptr;
        }

        inline static Comp comparef_ = Comp();
        Node* root_ = nullptr;

        bool isRed(Node* node)
        {
            if (node == nullptr)
                return false;
            return node->col_ == Color::RED;
        }
        size_t size(Node* node)
        {
            if (node == nullptr)
                return 0;
            return node->N_;
        }

        void flipColorsRed(Node* node)
        {
            node->col_ = Color::RED;
            node->left_->col_ = Color::BLACK;
            node->right_->col_ = Color::BLACK;
        }

        void flipColorsBlack(Node* node)
        {
            node->col_ = Color::BLACK;
            node->left_->col_ = Color::RED;
            node->right_->col_ = Color::RED;
        }
        //右红链接左旋: 更新链接， 更新颜色， 更新N_
        Node* rotateLeft(Node* node)
        {
            Node* right = node->right_;
            node->right_ = right->left_;
            right->left_ = node;

            right->col_ = node->col_;
            node->col_ = Color::RED;

            right->N_ = node->N_;
            node->N_ = size(node->left_) + size(node->right_) + 1;
            return right;
        }
        //左红链接右旋
        Node* rotateRight(Node* node)
        {
            Node* left = node->left_;
            left->right_ = node;
            node->left_ = left->right_;

            left->col_ = node->col_;
            node->col_ = Color::RED;


            left->N_ = node->N_;
            node->N_ = size(node->left_) + size(node->right_) + 1;
            return left;
        }
        Node* put(Node* node, K key, V val)
        {
            if (node == nullptr)
                return new Node(key, val, Color::RED);
            if (key == node->key_)
                node->val_ = val;
            else if (comparef_(key, node->key_))
                node->left_ = put(node->left_, key, val);
            else
                node->right_ = put(node->right_, key, val);
            

            //三行代码包含了插入的所有情况
            if (isRed(node->right_) && !isRed(node->left_)) node = rotateLeft(node);
            if (isRed(node->left_) && isRed(node->left_->left_)) node =  rotateRight(node);
            if (isRed(node->left_) && isRed(node->right_))   flipColorsRed(node);

            node->N_ = 1 + size(node->left_) + size(node->right_);
            return node;
        }
        Node* find(Node* node, K key)
        {
           while (node != nullptr && node->key_ != key)
           {
               if (comparef_(key, node->key_))
                   node = node->left_;
               else
                   node = node->right_;
           }
           return node;
        }
        Node* moveRedLeft(Node* node)
        {
            flipColorsBlack(node);
            if (isRed(node->right_->left_)) {
                node->right_ = rotateRight(node->right_);
                node = rotateLeft(node);
            }
            return node;
        }
    };

}
#endif