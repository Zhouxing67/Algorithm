#ifndef TOPOSHORTESTPATH_H_INCLUDED
#define TOPOSHORTESTPATH_H_INCLUDED
#include"EdgeWeightedDigraph.h"

/*
Dijkstra 非负权重的有向图单源最短路径

TopoSp 无环有向图
1.线性时间找最短路径 + Weight可以为负 + 变换权重正负号寻找最长路径
idea:
按照topological顺序relax所有顶点
证明 P426

note: 1.将weight全部取相反数  或者2.交换所有大小判断符号
*/

namespace alg4
{
    class TopoLP : public baseSP{
    private:
        void relax(EdgeWeightedDigraph* G, int v)
        {
            for (DiEdge e : G->getadj(v)) {
                int w = e.to();
                if (distTo[w] < distTo[v] + e.getWeight()) {            //注意符号方向
                    distTo[w] = distTo[v] + e.getWeight();
                    edgeTo[w] = e;
                }
            }
        }

        void getSP(EdgeWeightedDigraph* G, int s)
        {
            distTo[s] = 0.0;
            vector<int> topo_order = G->getTopo();
            for (int v : topo_order)
                relax(G, v);
        }

    public:
        TopoLP(EdgeWeightedDigraph* G, int src) : baseSP(G)
        {
            getSP(G, src);
        }
    };
}

#endif // TOPOSHORTESTPATH_H_INCLUDED
