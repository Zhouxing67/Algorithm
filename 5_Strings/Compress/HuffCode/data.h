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
    /*
    unordered_map<char, int> char_freq;
    priority_queue<Node*> pq_node;
    */
    
    //统计频率
    void init_char_freq(string filename, unordered_map<char, int>& freqs, size_t &chr_num)
    {
        char chr;
        ifstream ifs(filename);
        if (!ifs)
            throw std::runtime_error("Open file failed");
        while (ifs) {
            ifs.get(chr);
            if (chr >= 'A' || chr <= 'z' || chr == ' ' || chr == '\n') {
                if (freqs.find(chr) != freqs.end())
                    freqs[chr]++;
                else
                    freqs[chr] = 1;
                chr_num++;
            }
        }
    }

    //初始优先队列
    void init_pq_node(priority_queue<Node*>& pq, const unordered_map<char, int>& freqs)
    {
        for (const auto& [chr, freq] : freqs)
            pq.push(new Node(chr, freq));
    }

    //建树
    void init_tire(Node*& root, priority_queue<Node*> pq)
    {
        Node* left = nullptr, * right = nullptr;
        while (pq.size() > 1) {
            left = pq.top();
            pq.pop();
            right = pq.top();
            pq.pop();
            pq.push(new Node(left, right, left->freq_ + right->freq_));
        }
        root = pq.top();
    }

    //编码
    void init_codes(unordered_map<char, string>& codes, Node* root, string& code)
    {
        if (root->isleaf())
        {
            codes.insert({ root->chr_, code });
            return;
        }
        if (root->left_ != nullptr) {
            code.push_back('0');
            init_codes(codes, root->left_, code);
            code.pop_back();
        }
        if (root->right_ != nullptr) {
            code.push_back('1');
            init_codes(codes, root->right_, code);
            code.pop_back();
        }
    }
}


#endif