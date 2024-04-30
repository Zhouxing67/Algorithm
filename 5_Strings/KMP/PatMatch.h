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
       
    public:
        PatMatch(const string& pat, size_t R = std::numeric_limits<char>::max()) : pat_(pat), R_(R)
        {
            if (pat_.size() == 0)
                std::__throw_logic_error("Empty pattern is not allowed");
        }
        virtual int find(const string& str) = 0;
        
        const string& pat() const { return pat_; }
        const size_t& R() const { return R_; }
    };



    class Kmp : public PatMatch {
    private:
        //dfa_[chr][j] 表示在chr与模式串pat_[j]比较后，与chr的下一个字符相比较的模式串的字符索引
        vector<vector<int>> dfa_;
        void init_dfa()
        {
            string pat = this->pat();

            dfa_.resize(this->R(), vector<int>(pat.size(), 0));
            dfa_[pat[0]][0] = 1;//X表示重启状态
            for (int X = 0, j = 1; j < pat.size(); j++) {
                // 不匹配
                for (size_t chr = 0; chr < this->R(); chr++)
                    dfa_[chr][j] = dfa_[chr][X];
                // 匹配
                dfa_[pat[j]][j] = j + 1;
                //更新重启状态
                X = dfa_[pat[j]][X];
            }
        }
    public:
        Kmp(const string& pat) : PatMatch(pat)
        {
            init_dfa();
        }

        int find(const string& str)
        {
            string pat = this->pat();
            int i = 0, j = 0;
            for (; j < pat.size() && i < str.size(); i++)
                j = dfa_[str.at(i)][j];
            if (j == pat.size())
                return i - pat.size();
            return str.size();
        }

        const vector<vector<int>>& dfa() const { return dfa_; }
    };

    class Bm : public PatMatch {
    private:
        vector<int> next_;
        void init_next()
        {
            string pat = this->pat();
            next_.resize(this->R(), -1);
            for (auto i = 0; i < pat.size(); i++) {
                char chr = pat[i];
                next_[chr] = i;
            }
        }
    public:
        Bm(const string& pat) : PatMatch(pat)
        {
            init_next();
        }

        int find(const string& str) override
        {
            string pat = this->pat();
            int i = 0;
            while (i < str.size()) {
                int j = pat.size() - 1;
                while (j >= 0 && pat[j] == str[i + j])
                    j--;
                if (j == -1) return i;
                int skip = j < next_[str[i + j]] ? 1 : (j - next_[str[i + j]]);
                i += skip;
            }
            return str.size();
        }

    };
}

#endif