#include <iostream>
#include <fstream>
#include <bitset>
using std::bitset;
using namespace std;
int main()
{
    bitset<32> bits(-6);
    cout << bits << endl;
    bitset<32> bitss(0xf0000000);
    cout << bitss << endl;
    cout << 0b01100001;
}
