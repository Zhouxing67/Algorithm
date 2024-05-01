#ifndef DUMP_H
#define DUMP_H
#include <fstream>
#include <string>
#include <vector>


using std::vector;
using std::ifstream;
using std::string;

namespace alg4::util
{
    class Dump {
    private:
        void dump(vector<vector<char>>& bits);
        ifstream ifs;
        bool check();
    public:
        Dump(const string& filename);
        ~Dump() { ifs.close(); }
        void binary_dump();
        void picture_dump();

    };
}
#endif