#ifndef DATA_H
#define DATA_H

#include"Node.h"
#include<queue>
#include<string>
#include<unordered_map>
using std::priority_queue;
using std::string;
using std::unordered_map;

#include <fstream>
using std::ifstream;
using std::ofstream;

namespace alg4::str
{

    typedef priority_queue<Node*,std::vector<Node*>, Node_cmp> Node_pq;
    //统计频率
    void init_char_freq(ifstream & ifs, unordered_map<char, int>& freqs);
    //初始优先队列
    void init_pq_node(Node_pq& pq, const unordered_map<char, int>& freqs);
    //建树
    void init_tire(Node*& root, Node_pq pq);
    //编码
    void encode(unordered_map<char, string>& codes, Node* root, string& code);
    //构造字节流
    void init_data(ifstream& ifs, string& str, unordered_map<char, string>& codes);

}


#endif