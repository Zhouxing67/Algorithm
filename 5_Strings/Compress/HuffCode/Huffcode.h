#ifndef HUFF_CODE_H
#define HUFF_CODE_H
#include "data.h"
#include "Node.h"

namespace alg4::str
{

    void compress(const string& data, int& zeros);
    
    void expand(int zeros, Node* tie_root = nullptr, const string& filename = "./data/expand.txt");
}
#endif