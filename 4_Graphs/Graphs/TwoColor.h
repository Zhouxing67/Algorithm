#ifndef TWOCOLOR_H_INCLUDED
#define TWOCOLOR_H_INCLUDED

/*TODO   判断图存在多少个连通分量
思路:
所有未标记的节点 执行一遍完整DFS遍历
DFS代表从某一个节点出发 能到达的所有节点都会被标记
*/
#include"Graph.h"
namespace alg4::graph
{
    class TwoColor {
    private:
        vector<int> marked_;
        bool is_two_color_ = true;
        int COLOR = 1;

        void dfs(Graph* digraph, int source)
        {
            marked_[source] = COLOR;
            for (const auto& v : digraph->getadj(source)) {
                if (marked_[source] == COLOR)
                    COLOR = 1 - COLOR;
                if (!marked_[v])
                    dfs(digraph, v);
                else
                    is_two_color_ &= marked_[v] != marked_[source];
            }
        }

    public:
        TwoColor(Graph* G)
        {
            marked_.resize(G->getV());
            for (auto& i : marked_)
                i = -1;

            for (int v = 0; v < G->getV(); v++) {
                if (!marked_[v]) {
                    dfs(G, v);
                }
            }
        }

        bool is_two_color() { return is_two_color_; }

    };
}
#endif // DFSCC_H_INCLUDED
