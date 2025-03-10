#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "../../util/base_include.h"

namespace alg4::graph
{
    class Graph {
    private:
        int V;
        int E;
        vector<vector<int>> adj;            //邻接链表
        void addEdge(int v, int w)
        {
            adj[v].push_back(w);
            adj[w].push_back(v);
        }
    public:
        Graph(int v) :V(v), E(0) { adj.resize(v, vector<int>()); };
        Graph(string file)
        {
            ifstream ifs(file);
            string tmp;
            int lineNum = 0;
            if (!ifs.is_open())
                throw std::runtime_error("文件打开失败");
            while (getline(ifs, tmp)) {
                istringstream iss(tmp);
                int v1, v2;
                if (lineNum == 0) {
                    iss >> V;
                    adj.resize(V, vector<int>());
                }
                else if (lineNum == 1)
                    iss >> E;
                else {
                    iss >> v1 >> v2;
                    addEdge(v1, v2);
                }
                lineNum++;
            }
            ifs.close();
        };
        int getV() { return V; }
        int getE() { return E; }
        int degree(int v) { return adj[v].size(); }
        vector<int> getadj(int v) { return adj[v]; }

    };
}

#endif // GRAPH_H_INCLUDED
