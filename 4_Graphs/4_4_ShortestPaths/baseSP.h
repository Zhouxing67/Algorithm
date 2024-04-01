#ifndef BASESP_INCLUDE_H
#define BASESP_INCLUDE_H
#include"DiEdge.h"
#include"EdgeWeightedDigraph.h"

namespace alg4
{
    class baseSP {
    protected:
        vector<DiEdge> edgeTo;
        vector<double> distTo;
        bool isvalid = true;
        virtual void relax(EdgeWeightedDigraph* G, int v) = 0;
    public:
        baseSP() = default;
        baseSP(EdgeWeightedDigraph* G)
        {
            edgeTo.resize(G->getE(), EMPTY_EDGE);
            distTo.resize(G->getV(), std::numeric_limits<double>::max());
        }
        virtual ~baseSP() = default;

        virtual void getSP(EdgeWeightedDigraph* G, int s) = 0;
        

        //其他API
        double getdistTo(int v) { return distTo[v]; }
        bool hasPathTo(int v) { return distTo[v] != std::numeric_limits<double>::max(); }
        vector<DiEdge> pathTo(int v)
        {
            if (!isvalid)
            {
                cout << "不存在最短路径";
                return {};
            }
                vector<DiEdge> pathRes;
            stack<DiEdge> path;
            if (!hasPathTo(v))
                return {};
            for (DiEdge e = edgeTo[v]; e != EMPTY_EDGE; e = edgeTo[e.from()])
                path.push(e);
            while (!path.empty()) {
                DiEdge e = path.top();
                path.pop();
                pathRes.push_back(e);
            }
            return pathRes;  //未包含起点
        }
    };
}
#endif