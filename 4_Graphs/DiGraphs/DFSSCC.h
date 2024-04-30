#ifndef DFFSCC_INCLUDE_H
#define DFFSCC_INCLUDE_H
#include "Digraph.h"
#include "DFSorder.h"

namespace alg4::graph
{
    class KosarajuSSC {
    private:
        vector<bool> marked_;  //id_[v]表示所在连通集的编号
        vector<int> id_;
        int count_ = 0;

        void dfs(Digraph* digraph, int source)
        {
            marked_[source] = true;
            id_[source] = count_;
            for (const auto& v : digraph->getadj(source))
                dfs(digraph, v);
        }

    public:
        KosarajuSSC(Digraph* digraph)
        {
            id_.resize(digraph->getV());
            marked_.resize(digraph->getV());

            DFSorder order = DFSorder(digraph);
            //对序列order.reversePost 使用dfs
            for (const auto& v : order.reversePost()) {
                if (!marked_[v]) {
                    dfs(digraph, v);
                    count_++;
                }
            }
        }

        int count() { return count_; }

        int id(int vectex) { return id_[vectex]; }

        bool isstrongCC(int v, int w) { return id_[v] == id_[w]; }
    };
}
#endif












//include