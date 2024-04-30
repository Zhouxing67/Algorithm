#ifndef UTIL_STRFIND_H
#define UTIL_STRFIND_H
#include "PatMatch.h"

namespace alg4::util
{
    using alg4::str::Kmp;
    std::pair<char, char> bound(const string& str);
    void show_dfa_(const Kmp& kmp);
}
#endif