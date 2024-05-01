#include "geneCompress.h"
using namespace alg4::str;

//编译命令：g++ -o geneCompress_test -std=c++17 geneCompress_test.cpp ../util/StreamBitOut.cpp ../util/util_func.cpp
//运行命令：./geneCompress_test ../data/gene.txt ../data/outfile
int main(int argc, char* argv[])
{
    if (argc < 3)
        throw std::invalid_argument("need more argument");
    const string oringal_data =  argv[1];
    const string expand_file =   argv[2];
    
    string expand_data = "../data/expand.txt";
    GeneCompress genec(oringal_data, expand_file);

    genec.compress();
    genec.expand(expand_data);

    std::cout << alg4::util::compare(oringal_data, expand_data);
    return 0;
}
