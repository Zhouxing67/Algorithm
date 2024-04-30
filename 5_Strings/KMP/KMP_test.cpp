#include "PatMatch.h"
#include <iostream>
#include "util.h"
// g++ KMP_test.cpp util.cpp -o KMP_test.exe
int main()
{
    alg4::str::Kmp kmp ("ababac");
    std::string text;
    alg4::util::show_dfa_(kmp);

    
    while (std::cin >> text) {
        int index = kmp.find(text);

        if (index != text.size())
            std::cout << "Pattern found at index: " << index << std::endl;
        else
            std::cout << "Pattern not found" << std::endl;
    }


    return 0;
}
