#include <iostream>
#include <bits/stdc++.h>
using namespace std;
vector<char> readByte(char Byte, size_t bitnum)
{
    vector<char> vet;
    for (int i = 8 - bitnum; i >= 0; i -= bitnum) {
        //关键代码，掩码：(1 << bitnum) - 1
        char val = (Byte >> i) & ((1 << bitnum) - 1);
        vet.push_back(val);
    }
    return vet;
}
int main(int argc, char *argv[])
{
    bitset<8>b(85);
    cout << b;

    return 0;
}
