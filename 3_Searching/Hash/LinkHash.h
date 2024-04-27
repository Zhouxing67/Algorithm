#ifndef LINKHASH_INCLUDE_H
#define LINKHASH_INCLUDE_H
#include "Hash.h"
namespace alg4::search
{
    template<typename K, typename V>
    class linkHash : public Hash<K, V> {
    public:
        linkHash()
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
            data_[dataPos].push_back({ key, val });
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