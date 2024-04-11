#ifndef LAZYPRIMMST_H_INCLUDED
#define LAZYPRIMMST_H_INCLUDED

#include "EdgeWeightedGraph.h"

/*
延时删除的prim最小生成树
pre: 图是连通
idea: 随机起点 + 可到达边的最小值加入tree
note: 删除无效边(可达边的两个节点都已经标记)
*/

namespace alg4::graph
{
    class LazyPrimMST {
    private:
        queue<Edge> mst_;
        vector<bool> marked_;
        priority_queue<Edge, vector<Edge>, std::greater<Edge>> minpq_;
        double totalWeight_;

    public:
        LazyPrimMST(EdgeWeightedGraph* G) :totalWeight_(0.0)
        {
            marked_.resize(G->getV(), false);
        }

        queue<Edge> getMST(EdgeWeightedGraph* G)
        {
            visit(G, 0);
            while (!minpq_.empty()) {
                Edge e = minpq_.top();
                minpq_.pop();
                int v = e.either(), w = e.other(v);
                if (marked_[v] && marked_[w])
                    continue;
                //加入最小生成树
                mst_.push(e);
                totalWeight_ += e.getWeight();
                //visit新顶点
                if (!marked_[v])
                    visit(G, v);
                else
                    visit(G, w);
            }
            return mst_;
        }

        //节点v所有可达边加入优先队列
        void visit(EdgeWeightedGraph* G, int v)
        {
            marked_[v] = true;
            for (Edge e : G->getadj(v)) {
                int w = e.other(v);
                if (!marked_[w])
                    minpq_.push(e);
            }
        }

        double getWeight() { return totalWeight_; }

    };
}
#endif // LAZYPRIMMST_H_INCLUDED
