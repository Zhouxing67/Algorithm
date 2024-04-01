#ifndef GRAPH_UTILS_INCLUDE
#define GRAPH_UTILS_INCLUDE
#include <map>

using std::map;
namespace alg4
{
    class graph_util {
    public:
        static int getPQmin(map<int, double> minPQ)
        {
            double minval = std::numeric_limits<double>::max();
            int min_weight_key = 0;
            for (const auto& [vertex, weight] : minPQ) {
                if (weight < minval) {
                    min_weight_key = vertex;
                    minval = weight;
                }
            }
            return min_weight_key;
        }
        static void erasePQ(map<int, double> minPQ, int v)
        {
            auto it = minPQ.find(v);
            minPQ.erase(it);
        }
    };
}
#endif