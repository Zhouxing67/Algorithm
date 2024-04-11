#ifndef NEGATIVE_CYCLE_FINDER
#define NEGATIVE_CYCLE_FINDER
#include "EdgeWeightedDigraph.h"

namespace alg4::graph
{
    class negativeCycleFinder {
    private:
        vector<bool> onstack_;
        vector<bool> marked_;
        vector<DiEdge> cycle_;

        void dfs(const EdgeWeightedDigraph& ewg, int src)
        {
            onstack_[src] = true;
            marked_[src] = true;
            vector<DiEdge> edgeTo = ewg.getadj(src);
            for (const auto& edge : edgeTo) {
                int w = edge.to();
                if (!cycle_.empty())
                    return;
                else if (!marked_[w])
                    dfs(ewg, w);
                else if (onstack_[w]) {
                    for (DiEdge e = edge; e != edgeTo[src]; e = edgeTo[w])
                        cycle_.push_back(e);
                    cycle_.push_back(edgeTo[src]);
                }
            }
            onstack_[src] = false;
        }
    public:
        negativeCycleFinder(const EdgeWeightedDigraph& ewg)
        {
            onstack_.resize(ewg.getV(), false);
            marked_.resize(ewg.getV(), false);
        }
        vector<DiEdge> find_negative_cycle(const EdgeWeightedDigraph& ewg)
        {
            return cycle_;
        }

        bool hasNegativeCycle()
        {
            return cycle_.size() == 0;
        }

        vector<DiEdge> cycle()
        {
            return cycle_;
        }

    };
}
#endif