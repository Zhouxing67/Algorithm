#ifndef TRIS_ST_INCLUDE_H
#define TRIS_ST_INCLUDE_H
#include<string>
#include<memory>
#include<vector>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

namespace alg4::str
{
    template<typename V>
    class TrisSt
    {
    public:

        TrisSt() = default;
        ~TrisSt()
        {
            delete root_;
        }

        unique_ptr<V> get(const string& key)
        {
            Node* node = get(root_, key, 0);
            if (node == nullptr)
                return nullptr;
            return make_unique<V>(*(node->val_));
        }


        void put(const string& key, const V& val)
        {
            put(root_, key, val, 0);
        }

        int size()
        {
            return n;
        }

        vector<string> keysWithPrefix(const string& prefix)
        {
            vector<string> results;
            Node* node = get(root_, prefix, 0);
            collect(node, prefix, results);
            return results;
        }
        vector<string> keys()
        {
            return keysWithPrefix("");
        }

        const string longestPrefixOf(const string& query)
        {
            int size = longestPrefixOf(root_, query, 0, -1);
            if (size == -1)
                return string();
            else
                return query.substr(0, size);
        }

        void del(const string& key)
        {
            del(root_, key, 0);
        }


    private:
        size_t R_ = 256;
        struct Node
        {
            unique_ptr<V> val_ = nullptr;
            vector<Node*> next_;
            Node(size_t R)
            {
                //val_ = make_unique<V>(val);
                next_ = vector<Node*>(R, nullptr);
            }
            ~Node()
            {
                for (auto& child : next_) {
                    delete child;
                    child = nullptr;
                }
            }
        };
        Node* root_ = nullptr;
        int n = 0;

        void del(Node*& node, const string& key, int d)
        {
            if (node == nullptr) return;
            if (d == key.size()) {
                if (node->val_ != nullptr) {
                    n--;
                    node->val_ = nullptr;
                }
            }
            else {
                char c = key[d];
                del(node->next_[c], key, d + 1);
            }

            // remove subtrie rooted at node if it is completely empty
            if (node->val_ != nullptr)
                return;
            for (int c = 0; c < R_; c++)
                if (node->next_[c] != nullptr)
                    return;
            delete node;
            node = nullptr;
        }

        void put(Node*& node, const string& key, const V& val, int d)
        {
            if (node == nullptr)
                node = new Node(R_);
            if (d == key.size()) {
                if (node->val_ == nullptr) {
                    node->val_ = make_unique<V>(val);
                    n++;
                }
                else
                    *(node->val_) = val;
                return;
            }
            char c = key[d];
            put(node->next_[c], key, val, d + 1);
        }

        Node* get(Node* node, const string& key, int d)
        {
            if (node == nullptr || d == key.size())
                return node;
            char c = key[d];
            return get(node->next_[c], key, d + 1);
        }

        int longestPrefixOf(Node* node, const string& query, int d, int size)
        {
            if (node == nullptr)
                return size;
            if (d == query.size())
                return d;
            if (node.val != nullptr)
                size = d;
            char c = query[d];
            return longestPrefixOf(node.next[c], query, d + 1, size);
        }

        void collect(Node* node, string prefix, vector<string>& results)
        {
            if (node == nullptr)
                return;
            if (node->val_ != nullptr)
                results.push_back(prefix);
            for (char c = 0; c < R_; c++) {
                collect(node->next_[c], prefix + c, results);
            }
        }


    };
}
#endif