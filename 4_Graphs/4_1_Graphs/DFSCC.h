#ifndef DFSCC_H_INCLUDED
#define DFSCC_H_INCLUDED

/*TODO   判断图存在多少个连通分量
思路:
所有未标记的节点 执行一遍完整DFS遍历
DFS代表从某一个节点出发 能到达的所有节点都会被标记
*/
#include"Graph.h"
namespace alg4
{
    class DFSCC {
    private:
        vector<bool> marked_;
        vector<int> id_;     //id_[v]表示所在连通集的编号
        int count_ = 0;

        void dfs(Graph* digraph, int source)
        {
            marked_[source] = true;
            id_[source] = count_;
            for (const auto& v : digraph->getadj(source))
                if (!marked_[v])
                    dfs(digraph, v);
        }

    public:
        DFSCC(Graph* G)
        {
            marked_.resize(G->getV());
            id_.resize(G->getV());

            for (int v = 0; v < G->getV(); v++) {
                if (!marked_[v]) {
                    dfs(G, v);
                    count_++;
                }
            }
        }

        int count(Graph* G) { return count_; }

        int id(int vectex) { return id_[vectex]; }

        bool isstrongCC(int v, int w) { return id_[v] == id_[w]; }

    };
}
#endif // DFSCC_H_INCLUDED
