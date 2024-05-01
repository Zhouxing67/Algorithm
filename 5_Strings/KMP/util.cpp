#include "util.h"

std::pair<char, char> alg4::util::range(const string& str)
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

    std::pair<char, char> ran = range(kmp.pat());
    for (char chr = ran.first; chr <= ran.second; chr++) {
        cout << chr << " : ";
        for (auto i : dfa_[chr])
            cout << i << " ";
        cout << endl;
    }
    cout << endl;
}