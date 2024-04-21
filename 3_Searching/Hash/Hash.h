#ifndef HASH_INCLUDE_H
#define HASH_INCLUDE_H
#include <vector>
#include <list>
#include <utility>
#include <memory>
using std::list;
using std::vector;
using std::pair;
#include <functional>

namespace alg4::search
{
    template<typename K, typename V>
    class baseHash {
    public:
        explicit baseHash() = default;
        baseHash(size_t M) : M_(M) { }
        virtual std::unique_ptr<V> get(K key) = 0;
        virtual void del(K key) = 0;
        virtual void put(K key, V val) = 0;

        size_t size() { return N_; }
    protected:
        static inline std::hash<K> hash_ = std::hash<K>();
        size_t N_ = 0;
        size_t M_ = 97;
    };


    template<typename K, typename V>
    class linkHash : public baseHash<K, V> {
    public:
        linkHash() : baseHash<K, V>()
        {
            data_.resize(this->M_, list<pair<K, V>>());
        }

        std::unique_ptr<V> get(K key) override
        {
            size_t dataPos = this->hash_(key) % this->M_;
            for (auto itr = data_[dataPos].begin(); itr != data_[dataPos].end(); itr++) {
                if (itr->first == key)
                    return std::make_unique<V>(itr->second);
            }
            return nullptr;
        }

        void put(K key, V val) override
        {
            size_t dataPos = this->hash_(key) % this->M_;
            for (auto itr = data_[dataPos].begin(); itr != data_[dataPos].end(); itr++) {
                if (itr->first == key) {
                    itr->second = val;
                    return;
                }
            }
            data_[dataPos].push_back({key, val});
        }

        void del(K key) override
        {
            size_t dataPos = this->hash_(key) % this->M_;
            auto target = data_[dataPos].begin();
            for (auto itr = data_[dataPos].begin(); itr != data_[dataPos].end(); itr++) {
                if (itr->first == key) {
                    target = itr;
                    break;
                }
            }
            data_[dataPos].erase(target);
        }
    private:
        vector<list<pair<K, V>>> data_;
    };

}
#endif