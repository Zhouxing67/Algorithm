#ifndef DFSPATH_H_INCLUDE
#define DFSPATH_H_INCLUDE

#include "traversal_base.h"
namespace alg4::graph
{
    class DFSPath : public traversalBase{
    private:
  
        void dfs(Graph* graph, int src)
        {
            marked_[src] = true;
            for (const auto v : graph->getadj(src)) {
                if (!marked_[v]) {
                    edgeTo_[v] = src;
                    dfs(graph, v);
                }
            }
        }
    public:
        DFSPath(Graph* graph, int src) : traversalBase(graph)
        {
            dfs(graph, src);
        }

    };
}

#endif