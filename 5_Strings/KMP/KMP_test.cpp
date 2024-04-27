#include "PatMatch.h"
#include <iostream>

int main()
{
    alg4::str::PatMatch kmp("ababac");
    std::string text;
    alg4::str::show_dfa_(kmp);
    while (std::cin >> text) {
        int index = kmp.kmp_find(text);
        if (index != kmp.bm_find(text)) {
            cout << "error " << endl;
            continue;
        }
        if (index != text.size())
            std::cout << "Pattern found at index: " << index << std::endl;
        else
            std::cout << "Pattern not found" << std::endl;
    }


    return 0;
}
