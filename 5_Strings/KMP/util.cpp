#include "util.h"

std::pair<char, char> alg4::util::bound(const string& str)
{
    char min = 127, max = 0;
    for (auto chr : str) {
        min = min < chr ? min : chr;
        max = max > chr ? max : chr;
    }
    return { min, max };
}

void alg4::util::show_dfa_(const Kmp& kmp)
{
    auto dfa_ = kmp.dfa();
    cout << "    ";
    for (size_t i = 0; i < kmp.pat().size(); i++)
        cout << i << " ";
    cout << endl;

    auto range = bound(kmp.pat());
    for (char chr = range.first; chr <= range.second; chr++) {
        cout << chr << " : ";
        for (auto i : dfa_[chr])
            cout << i << " ";
        cout << endl;
    }
    cout << endl;
}