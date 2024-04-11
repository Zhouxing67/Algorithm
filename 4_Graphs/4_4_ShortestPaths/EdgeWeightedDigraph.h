#ifndef EDGEWEIGHTEDDIGRAPH_H_INCLUDED
#define EDGEWEIGHTEDDIGRAPH_H_INCLUDED
#include"DiEdge.h"
/*
加权 有向图的定义
*/
namespace alg4::graph
{
    class EdgeWeightedDigraph {
    private:
        int V;
        int E;
        vector<vector<DiEdge>> adj;
        vector<int> indegree_;

    public:
        EdgeWeightedDigraph(int V) : V(V)
        {
            adj.resize(V, vector<DiEdge>());
            indegree_.resize(V, 0);
        }
        EdgeWeightedDigraph(string file)
        {
            std::ifstream infile(file);
            string tmp;
            int lineNum = 0;
            if (!infile.is_open())
                throw std::runtime_error("文件打开失败");
            while (std::getline(infile, tmp)) {
                std::istringstream iss(tmp);
                int v1, v2;
                double weight;
                if (lineNum == 0) {
                    iss >> V;
                    adj.resize(V, vector<DiEdge>());
                    indegree_.resize(V, 0);
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
        void addEdge(int v, int w, double weight)
        {
            DiEdge tmp(v, w, weight);
            addEdge(v, tmp);
        }

        void addEdge(int v ,const DiEdge &edge)
        {
            adj[v].push_back(edge);
            indegree_[edge.to()]++;
        }
        int getV() const { return V; }
        int getE() const { return E; }
        int outdegree(int v) const{ return adj[v].size(); }
        int indegree(int v) const { return indegree_[v]; }
        vector<DiEdge> getadj(int v) { return adj[v]; }
        vector<DiEdge> getadj(int v) const { return getadj(v); }
        set<DiEdge> getAllEdges()
        {
            set<DiEdge> allEdges;
            for (vector<DiEdge> tmp : adj) {
                for (DiEdge e : tmp) {
                    allEdges.insert(e);
                }
            }
            return allEdges;
        }
        vector<int> getTopo()
        {
            queue<int> topo;
            vector<int> temp = indegree_, res;
            for (int i = 0; i != temp.size(); i++)
                if (temp[i] == 0)
                    topo.push(i);
            while (!topo.empty()) {
                int v = topo.front();
                if (v) {
                    cout << "有环图无法进行拓扑排序" << endl;
                    return {};
                }
                res.push_back(v);
                for (const auto& edge : adj[v]) {
                    int w = edge.to();
                    indegree_[w]--;
                    if (indegree_[w] == 0)
                        topo.push(w);
                }
                topo.pop();
            }
            return res;
        }
    };
}

#endif // EDGEWEIGHTEDDIGRAPH_H_INCLUDED
