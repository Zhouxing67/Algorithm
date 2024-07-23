#ifndef EDGEWEIGHTEDGRAPH_H_INCLUDED
#define EDGEWEIGHTEDGRAPH_H_INCLUDED
#include "../../util/base_include.h"
#include"Edge.h"
/*
实现带带权重的无向图
*/
namespace alg4::graph
{
    class EdgeWeightedGraph {
    private:
        int V;
        int E;
        vector<vector<Edge>> adj;

    public:

        EdgeWeightedGraph(int V) : V(V), E(0)
        {
            adj.resize(V, vector<Edge>());
        }

        EdgeWeightedGraph(string file)
        {
            //cout << file << endl;
            std::ifstream infile(file);
            string tmp;
            int lineNum = 0;
            if (!infile.is_open()) {
                throw std::runtime_error("文件打开失败");
            }

            while (std::getline(infile, tmp)) {
                std::istringstream iss(tmp);
                int v1, v2;
                double weight;
                if (lineNum == 0) {
                    iss >> V;
                    adj.resize(V, vector<Edge>());
                }
                else if (lineNum == 1)
                    iss >> E;
                else {
                    iss >> v1 >> v2 >> weight;
                    addEdge(v1, v2, weight);
                }
                lineNum++;
            }
        }
        int getV() { return V; }
        int getE() { return E; }
        int degree(int v) { return adj[v].size(); }
        vector<Edge> getadj(int v) { return adj[v]; }
        void addEdge(int v, int w, double weight)
        {
            Edge edge(v, w, weight);
            adj[v].push_back(edge);
            adj[w].push_back(edge);
        }
        set<Edge> getAllEdges()
        {
            set<Edge> allEdges;
            for (vector<Edge> tmp : adj) {
                for (Edge e : tmp) {
                    allEdges.insert(e);
                }
            }
            return allEdges;
        }
    };
}

#endif // EDGEWEIGHTEDGRAPH_H_INCLUDED
