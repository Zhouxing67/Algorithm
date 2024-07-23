#include "Dump.h"
#include "util_func.h"
#include "../../util/color_def.h"
#include <iostream>

using std::cerr;
using std::endl;
using std::cout;

alg4::util::Dump::Dump(const string& filename) : ifs(filename)
{
    bool open = ifs.is_open();
    check();
}
void alg4::util::Dump::dump(vector<vector<char>>& bits)
{

    if (!check())
        return;
    ifs.seekg(0, std::ios::beg);
    char byte;
    while (ifs) {
        ifs.get(byte);
        bits.push_back(readOneBit(byte));
    }
    ifs.clear();
}

void alg4::util::Dump::binary_dump()
{
    vector<vector<char>> bits;
    dump(bits);
    for (int i = 0; i < bits.size(); i++) {
        for (size_t j = 0; j < 8; j++)
            cout << bits[i][j] - '\0';
        if (i & 1)
            cout << endl;
    }
    cout << endl;
}

void alg4::util::Dump::picture_dump()
{
    vector<vector<char>> bits;
    dump(bits);
    for (int i = 0; i < bits.size(); i++) {
        for (size_t j = 0; j < 8; j++)
            if (bits[i][j])
                cout << WHITE_SQUARE << "  " << ANSI_COLOR_RESET;
            else
                cout << BROWN_SQUARE << "  " << ANSI_COLOR_RESET;
        if (i & 1)
            cout << endl;
    }
    cout << endl;
}

bool alg4::util::Dump::check()
{
    if (ifs.is_open())
        return true;
    cerr << "open file failed" << endl;
    return false;
}