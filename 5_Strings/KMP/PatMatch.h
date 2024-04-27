#ifndef KMP_INCLUDE_H
#define KMP_INCLUDE_H
#include <string>
#include <vector>
using std::vector;
using std::string;
#include <limits>
#include <iostream>
using std::cout;
using std::endl;

#include <utility>
using std::pair;
namespace alg4::str
{
    class PatMatch
    {
    private:
        string pat_;
        size_t R_;
        vector<vector<int>> dfa_;
        vector<int> next_;

        void init_next()
        {
            next_.resize(R_, -1);
            for (auto i = 0; i < pat_.size(); i++) {
                char chr = pat_[i];
                next_[chr] = i;
            }
        }

        void init_dfa()
        {
            dfa_.resize(R_, vector<int>(pat_.size(), 0));
            dfa_[pat_[0]][0] = 1;//X表示重启状态
            for (int X = 0, j = 1; j < pat_.size(); j++) {
                // 不匹配
                for (size_t chr = 0; chr < R_; chr++)
                    dfa_[chr][j] = dfa_[chr][X];
                // 匹配
                dfa_[pat_[j]][j] = j + 1;
                //更新重启状态
                X = dfa_[pat_[j]][X];
            }
        }

    public:
        PatMatch(const string& pat, size_t R = std::numeric_limits<char>::max()) : pat_(pat), R_(R)
        {
            if (pat_.size() == 0)
                std::__throw_logic_error("Empty pattern is not allowed");
            init_dfa();
            init_next();
        }

        int kmp_find(const string& str)
        {
            int i = 0, j = 0;
            for (; j < pat_.size() && i < str.size(); i++)
                j = dfa_[str.at(i)][j];
            if (j == pat_.size())
                return i - pat_.size();
            return str.size();
        }

        int bm_find(const string& str)
        {
            int i = 0, j = pat_.size() - 1;
            while ( i < str.size()) {
                while (j >= 0 && pat_[j] == str[i + j])
                    j--;
                if (j == -1)
                    return i;
                int skip = j - next_[str[i + j]];
                if (skip < 1)
                    skip = 1;
                
                i += skip;
                j = pat_.size() - 1;
            }
            return str.size();
        }

        const vector<vector<int>>& dfa() const { return dfa_; }

        const string & pat() const { return pat_; }
    };

    std::pair<char, char> bound(const string& str)
    {
        char min = 127, max = 0;
        for (auto chr : str)
        {
            min = min < chr ? min : chr;
            max = max > chr ? max : chr;
        }
        return { min, max };
    }

    void show_dfa_(const PatMatch& patmat)
    {
        auto dfa_ = patmat.dfa();
        cout << "    ";
        for (size_t i = 0; i < patmat.pat().size(); i++)
            cout << i << " ";
        cout << endl;

        auto range = bound(patmat.pat());
        for (char chr = range.first; chr <= range.second; chr++)
        {
            cout << chr << " : ";
            for (auto i : dfa_[chr])
                cout << i << " ";
            cout << endl;
        }
        cout << endl;
    }
}
#endif