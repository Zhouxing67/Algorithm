#ifndef PRIMMST_H_INCLUDED
#define PRIMMST_H_INCLUDED

#include "EdgeWeightedGraph.h"
#include"../utils.h"

/*
即时删除的prim最小生成树
idea: 随机起点 + 可到达边的最小值加入tree
note:
1.lazy模式 会将Edge都加入queue ==》 priority queue
2.即时 在加入queue进行判断: 无效边+非最小边 被拒绝
3.数据结构:
edgeTo_[w] w距离tree最近的edge 或者NULL
dist[w]=edgeTo_[w].weight
indexQueue 用map<w,weight>实现,保存待遍历的横切边

相比较于Lazy模式  indexPQ中的可达边数量是常数级别
*/
namespace alg4::graph
{
    class PrimMST {
    private:
        vector<Edge> edgeTo_;
        vector<double> distTo_;
        vector<bool> marked_;
        map<int, double> indexPQ_;
        double totalWeight_;

    public:
        PrimMST(EdgeWeightedGraph* G) :totalWeight_(0.0)
        {
            edgeTo_.resize(G->getV());
            distTo_.resize(G->getV(), std::numeric_limits<double>::max());
            marked_.resize(G->getV(), false);
        }

        vector<Edge> getMST(EdgeWeightedGraph* G)
        {
            distTo_[0] = 0.0;
            indexPQ_[0] = 0.0;
            while (!indexPQ_.empty()) {
                int v = graph_util::getPQmin(indexPQ_);     //相比较于Lazy模式  indexPQ中的可达边数量是常数级别
                totalWeight_ += indexPQ_[v];
                graph_util::erasePQ(indexPQ_,v);
                visit(G, v);     //最近节点加入树中
            }
            return edgeTo_;
        }

        //节点v所有可达边
        void visit(EdgeWeightedGraph* G, int v)
        {
            marked_[v] = true;
            for (Edge e : G->getadj(v)) {
                int w = e.other(v);
                if (marked_[w]) // 无效边
                    continue;
                else if (e.getWeight() >= distTo_[w])  //非最小边
                    continue;
                else {//更新路径， 更新最小权值， 将边加入预备map
                    edgeTo_[w] = e; 
                    distTo_[w] = e.getWeight();
                    indexPQ_[w] = distTo_[w];         
                }
            }
        }

        double getWeight() { return totalWeight_; }
        vector<Edge> getEdgeTo() { return edgeTo_; }

    };

}
#endif // PRIMMST_H_INCLUDED
