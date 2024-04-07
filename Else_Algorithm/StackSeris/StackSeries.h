#ifndef STACKSERIES_INCLUDE_H
#define STACKSERIES_INCLUDE_H
#include "../../base_include.h"

/*

回溯算法本质上是一种深度优先搜索（DFS）

在回溯算法中，通常会沿着一个路径尽可能深地搜索，直到达到某个终止条件或者无法继续搜索为止。然后，回溯到上一个状态，尝试其他可能的路径。

具体来说，回溯算法通过不断地向下探索每个可能的决策路径来解决问题。
在搜索的过程中，如果当前路径不满足问题的条件，或者已经搜索完所有可能的情况，我们就会回溯到上一个状态，尝试其他可能的路径。

通过容器记录状态， 将这个容器叫做状态容器

在回溯算法中，每一次的递归调用都会修改状态容器。而当递归调用返回后，都要需要确保这次递归调用对状态容器的影响被完全消除，
状态容器在递归调用前后是一致的，通常需要手动恢复被递归调用改变了的状态容器。

复杂的回溯算法需要保存多个状态， 需要多个状态容器， 每个状态容器都满足上述条件。

关键点：终止条件， 回溯的条件（check()函数）， 管理状态容器（）

*/
namespace  alg4
{
    class StackSeries
    {

    private:
        //i 表示当前处理字符在入栈序列的位置，状态容器：out_series, st
        static void backtrace(const string input_series, int i, vector<char>& out_series, vector<vector<char>>& allseries, stack<char>& st)
        {
            //终止条件1
            if (out_series.size() == input_series.size()) {
                allseries.push_back(out_series);
                return;
            }
            //pop
            if (!st.empty()) {
                //改变状态容器
                out_series.push_back(st.top());
                st.pop();

                backtrace(input_series, i, out_series, allseries, st);

                //恢复状态容器
                st.push(out_series.back());
                out_series.pop_back();
            }
            //push
            if (i != input_series.size()) {
                //改变状态容器
                st.push(input_series[i]);

                backtrace(input_series, i + 1, out_series, allseries, st);

                //恢复状态容器
                st.pop();
            }
        }
    public:
        static vector<vector<char>> getStackSeries(string input_series)
        {
            vector<char> out_series;
            vector<vector<char>> allseries;
            stack<char> st;
            backtrace(input_series, 0, out_series, allseries, st);
            return allseries;
        }
    };
}


#endif