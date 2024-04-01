#ifndef BELLMANFORDSP_H_INCLUDED
#define BELLMANFORDSP_H_INCLUDED
#include"EdgeWeightedDigraph.h"
#include "NegativeCycleFinder.h"
/*
定理:
1.distTo[S]=0,其他点无穷大。任意顺序relax所有边
2.1 重复V(顶点个数)轮  则停止
2.2 edgeTo[]存在负权重环  则停止

3.note:优化:
idea: 只有上一轮distTo[]发生变化的顶点指出的边才可能改变其他distTo[]的值,FIFO队列记录这样的顶点
==》 一轮代表执行一次relax(G,v)  ？？
queue1 保存即将被放松的顶点
bool[] 判断顶点是否已经存在于queue1
*/

namespace alg4
{
    class BellmanSP : public baseSP{
    private:
        vector<bool> onQ;
        queue<int> fifo;        //待执行relax的顶点
        vector<DiEdge> cycle_;
        int relaxCalls = 0;

        
        void relax(EdgeWeightedDigraph* G, int v)
        {
            for (DiEdge e : G->getadj(v)) {
                int w = e.to();
                if (distTo[w] > distTo[v] + e.getWeight()) {            //注意符号方向
                    distTo[w] = distTo[v] + e.getWeight();
                    edgeTo[w] = e;
                    //加入queue
                    if (onQ[w] == false) {
                        fifo.push(w);
                        onQ[w] = true;
                    }
                }
                if (++relaxCalls % G->getV() == 0) {
                    findNegativeCycle();  //这里我就不实现了
                    //                if(hasNCycle) return;
                }
            }
        }

        void findNegativeCycle()
        {
            EdgeWeightedDigraph ewg(edgeTo.size());
            for (int i = 0; i != edgeTo.size(); i++)
                ewg.addEdge(i, edgeTo[i]);
            negativeCycleFinder finder(ewg);
            cycle_ = finder.find_negative_cycle(ewg);
        }

        void getSP(EdgeWeightedDigraph* G, int s)
        {
            distTo[s] = 0.0;
            onQ[s] = true;
            fifo.push(s);
            while (!fifo.empty() && cycle_.empty()) {
                int v = fifo.front();
                fifo.pop();
                onQ[v] = false;
                relax(G, v);
            }
            if (!cycle_.empty())
                isvalid = false;
        }

    public:
        BellmanSP(EdgeWeightedDigraph* G, int src) : baseSP(G)
        {
            onQ.resize(G->getV(), false);
            getSP(G, src);
        }
    };
}


#endif // BELLMANFORDSP_H_INCLUDED
