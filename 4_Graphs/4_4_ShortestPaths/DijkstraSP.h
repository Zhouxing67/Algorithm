#ifndef DIJKSTRASP_H_INCLUDED
#define DIJKSTRASP_H_INCLUDED

#include"baseSP.h"
#include"../utils.h"
/*
非负权重 有向图
类似于即时的prim算法
1.将dist[Start]=0,其他distTo[]初始化为无穷大
2.重复将distTo[]中最小非树节点V =>relax(G,V)
3.直到所有顶点都在树或所有非树顶点distTo无限大
*/
//baseSP为SP的基类，未被定义为虚函数
namespace alg4::graph
{
    class DijkstraSP : public baseSP {
    private:

        map<int, double> minPQ;    
        //relax 松弛API
        void relax(EdgeWeightedDigraph* G, int v)
        {
            for (DiEdge e : G->getadj(v)) {
                int w = e.to();
                //w到s的距离更新
                if (distTo[v] + e.getWeight() < distTo[w]) {
                    distTo[w] = distTo[v] + e.getWeight();
                    edgeTo[w] = e;
                    minPQ[w] = distTo[w];     //update or insert
                }
            }
        }

        void getSP(EdgeWeightedDigraph* G, int s)
        {
            distTo[s] = 0.00;
            minPQ[s] = distTo[s];
            while (!minPQ.empty()) {
                int v = graph_util::getPQmin(minPQ);
                graph_util::erasePQ(minPQ, v);
                relax(G, v);
            }
        }

    public:
        explicit DijkstraSP(EdgeWeightedDigraph* G, int src) : baseSP(G)
        {
            /* edgeTo.resize(G->getV(), EMPTY_EDGE);
            distTo.resize(G->getV(), std::numeric_limits<double>::max()); */
            getSP(G, src);
        }
    };
}
#endif // DIJKSTRASP_H_INCLUDED
