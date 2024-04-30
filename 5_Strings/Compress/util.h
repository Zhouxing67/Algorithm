#ifndef UTIL_COMPRESS_H
#define UTIL_COMPRESS_H
#include <fstream>
#include <string>
#include <vector>

using std::vector;
using std::ifstream;
using std::string;

namespace alg4::util
{
    bool compare(const string& oringal_data, const string& expand_data);
    vector<int> readOneByte(char Byte, size_t bitnum = 1);
}
#endif
