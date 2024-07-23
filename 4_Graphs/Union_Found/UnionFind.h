#ifndef UNIONFIND_H_INCLUDED
#define UNIONFIND_H_INCLUDED
#include"../../util/base_include.h"
/*
实现weighted union find
小树加入大树 从而减少树的高度
*/

namespace alg4::graph
{
    class UnionFind {
    private:
        vector<int> parent_;
        vector<int> sz_;
        int unionCount_;
    public:
        UnionFind(int vertexNum)
            :unionCount_(vertexNum)
        {
            parent_.resize(vertexNum);
            sz_.resize(vertexNum, 1);
            for (int i = 0; i < vertexNum; i++)
                parent_[i] = i;
        }
        int getUnionNum() { return unionCount_; }

        //API= find,union,connected
        bool connected(int v, int w)
        {
            return find_root(v) == find_root(w);
        }
        int find_root(int p)
        {
            while (p != parent_[p])
                p = parent_[p];
            return p;
        }
        void unionV(int v, int w)
        {
            int i = find_root(v), j = find_root(w);
            if (i == j)
                return;
            if (sz_[i] < sz_[j]) {
                parent_[i] = j;
                sz_[j] += sz_[i];
            }
            else {
                parent_[j] = i;
                sz_[i] += sz_[j];
            }
            unionCount_--;
        }
    };
}

#endif // UNIONFIND_H_INCLUDED
