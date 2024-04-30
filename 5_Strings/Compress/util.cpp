#include "util.h"
bool alg4::util::compare(const string& oringal_data, const string& expand_data)
{
    ifstream ifs0(oringal_data);
    ifstream ifs1(expand_data);
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
    if (!ifs0.eof())
        return false;
    if (!ifs1.eof())
        return false;
    ifs0.close();
    ifs1.close();
    return true;
}

vector<int> alg4::util::readOneByte(char Byte, size_t bitnum = 1)
{
    vector<int> vet;
    for (int i = 8 - bitnum; i >= 0; i -= bitnum) {

        //关键代码，掩码：(1 << bitnum) - 1
        int val = (Byte >> i) & ((1 << bitnum) - 1);
        vet.push_back(val);
    }
    return vet;
}