#include "util_func.h"

bool alg4::util::compare(const string& oringal_data, const string& expand_data)
{
    ifstream ifs0(oringal_data), ifs1(expand_data);
    while (ifs0 && ifs1) {
        char oringal_byte, expand_byte;
        ifs0.get(oringal_byte);
        ifs1.get(expand_byte);
        if (oringal_byte != expand_byte) {
            ifs0.close();
            ifs1.close();
            return false;
        }
    }
    if (!ifs0.eof()) return false;
    if (!ifs1.eof()) return false;
    ifs0.close();
    ifs1.close();
    return true;
}

vector<char> alg4::util::readByte(unsigned char Byte, size_t bitnum)
{
    vector<char> vet;
    for (int i = 8 - bitnum; i >= 0; i -= bitnum) {
        //关键代码，掩码：(1 << bitnum) - 1
        char val = (Byte >> i) & ((1 << bitnum) - 1);
        vet.push_back(val);
    }
    return vet;
}

vector<char> alg4::util::readOneBit(unsigned char Byte)
{
    return alg4::util::readByte(Byte, 1);
}



