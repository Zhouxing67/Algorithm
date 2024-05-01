#ifndef UTIL_FUNC_H
#define UTIL_FUNC_H
#include <fstream>
#include <string>
#include <vector>
#include <stddef.h>

using std::vector;
using std::ifstream;
using std::string;

#include <iostream>

using std::cerr;
using std::endl;
using std::cout;

namespace alg4::util
{
    bool compare(const string& oringal_data, const string& expand_data);
    vector<char> readOneBit(unsigned char Byte);
    vector<char> readByte(unsigned char Byte, size_t bitnum);
}
#endif
