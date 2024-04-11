#ifndef DFSTOPO_H_INCLUDED
#define DFSTOPO_H_INCLUDED
#include"Digraph.h"
#include"DFSDirectedCycle.h"
#include"DFSorder.h"
/*
拓扑排序  DFS+一行代码

BFS是将入度为零的先加入queue
*/

namespace alg4::graph
{
    class DFSTopo {
    public:
        vector<int> getTopo(Digraph* G)
        {
            DFSDirectedCycle cycle = DFSDirectedCycle(G);
            if (cycle.hasCycle(G))
                return {};

            DFSorder order = DFSorder(G);
            return order.reversePost();
        }
    };
}
#endif // DFSTOPO_H_INCLUDED
