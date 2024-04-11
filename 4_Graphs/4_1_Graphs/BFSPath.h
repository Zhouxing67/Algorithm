#ifndef BFSPATH_H_INCLUDED
#define BFSPATH_H_INCLUDED

#include"traversal_base.h"
namespace alg4::graph
{
    class BFSPath : public traversalBase{     //父节点

    private:
         //src:  bfs 的起点
        void bfs(Graph* G, int src)
        {
            queue<int> que;
            marked_[src] = true;
            que.push(src);

            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (int w : G->getadj(v))
                    if (!marked_[w]) {
                        edgeTo_[w] = v;          //区别于BFS代码
                        marked_[w] = true;
                        que.push(w);
                    }
            }
        }
    public:
        BFSPath(Graph* graph, int src) : traversalBase(graph)
        {
            bfs(graph, src);
        }

    };
}
#endif // BFSPATH_H_INCLUDED
