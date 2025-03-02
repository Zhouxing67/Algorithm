#ifndef STACKSERIES_INCLUDE_H
#define STACKSERIES_INCLUDE_H
#include "../../util/base_include.h"
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