#ifndef DFSORDER_INCLUDE_H
#define DFSORDER_INCLUDE_H
#include "Digraph.h"

namespace alg4::graph
{
    class DFSorder {
    private:
        vector<bool> marked_;
        stack<int> reversePost_;
        vector<int> pre_;
        queue<int> post_;

        void dfs(Digraph* G, int source)
        {
            pre_.push_back(source);
            marked_[source] = true;
            for (int w : G->getadj(source)) {
                if (!marked_[w])
                    dfs(G, w);
            }
            reversePost_.push(source);
            post_.push(source);
        }
    public:
        DFSorder(Digraph* digraph)
        {
            marked_.resize(digraph->getV());
            for (int i = 0; i < digraph->getV(); i++)
                if (!marked_[i])
                    dfs(digraph, i);
        }

        vector<int> pre() { return pre_; }
        vector<int> post()
        {
            vector<int> post(post_.size());
            int i = 0;
            while (!post_.empty()) {
                post[i++] = post_.front();
                post_.pop();
            }

            return post;
        }
        vector<int> reversePost()
        {
            vector<int> reversePost(reversePost_.size());
            int i = 0;
            while (!reversePost_.empty()) {
                reversePost[i++] = reversePost_.top();
                reversePost_.pop();
            }
            return reversePost;
        }
    };
}
#endif