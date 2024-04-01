#ifndef TRAVERSAL_BASE
#define TRAVERSAL_BASE
#include "../../base_include.h"
#include "Graph.h"
namespace alg4
{
    class traversalBase {
    protected:
        vector<bool> marked_;
        vector<int> edgeTo_;
    public:
        traversalBase(Graph* graph)
        {
            marked_.resize(graph->getV());
            edgeTo_.resize(graph->getV());
        }
        virtual ~traversalBase() = default;

        //src到src的路径
        vector<int> pathTo(int desc, int src)
        {
            vector<int> path;
            for (int i = desc; i != src; i = edgeTo_[i])
                path.push_back(i);
            path.push_back(src);
            return path;
        }
    };

} // namespace alg4

#endif