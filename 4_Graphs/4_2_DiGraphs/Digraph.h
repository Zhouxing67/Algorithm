#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED
#include "../../base_include.h"

namespace alg4::graph
{
    class Digraph {
    private:
        int vertex_;
        int edge;
        vector<vector<int>> adj;            //邻接链表
        void addEdge(int v, int w)
        {
            adj[v].push_back(w);            //区别于无向图
        }
    public:
        Digraph(int v) :vertex_(v), edge(0)
        {
            adj.resize(v, vector<int>());
        };
        Digraph(string file)
        {
            std::ifstream infile(file);
            string tmp;
            int lineNum = 0;
            while (std::getline(infile, tmp)) {
                std::istringstream iss(tmp);
                int v1, v2;
                if (lineNum == 0) {
                    iss >> vertex_; adj.resize(vertex_, vector<int>());
                }
                else if (lineNum == 1)
                    iss >> edge;
                else {
                    iss >> v1 >> v2;
                    addEdge(v1, v2);
                }
                lineNum++;
            }
        };
        int getV() { return vertex_; }
        int getE() { return edge; }
        int degree(int v) { return adj[v].size(); }
        vector<int> getadj(int v) { return adj[v]; }

        //反转图
        Digraph* reverseG()
        {
            Digraph* revG = new Digraph(vertex_);
            for (int v = 0;v < vertex_;v++) {
                for (int w : getadj(v))
                    revG->addEdge(w, v);
            }
            return revG;
        }

    };
}
#endif // DIGRAPH_H_INCLUDED
