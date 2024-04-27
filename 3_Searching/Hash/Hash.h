#ifndef HASH_INCLUDE_H
#define HASH_INCLUDE_H
#include <vector>
#include <list>
#include <utility>
#include <memory>
using std::list;
using std::vector;
using std::pair;
using std::unique_ptr;
#include <functional>

namespace alg4::search
{
    template<typename K, typename V>
    class Hash {
    public:
        explicit Hash() = default;
        Hash(size_t M) : M_(M) { }
        virtual std::unique_ptr<V> get(K key) = 0;
        virtual void del(K key) = 0;
        virtual void put(K key, V val) = 0;

        size_t size() { return N_; }
    protected:
        static inline std::hash<K> hash_ = std::hash<K>();
        size_t N_ = 0;
        size_t M_ = 97;
    };
}
#endif