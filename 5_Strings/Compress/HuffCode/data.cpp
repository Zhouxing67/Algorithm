#include "data.h"

void alg4::str::init_char_freq(ifstream & ifs, unordered_map<char, int>& freqs)
{
    char chr;
    while (ifs.get(chr)) {
        if (chr >= 'A' || chr <= 'z' || chr == ' ' || chr == '\n' || chr >= '0' || chr <= '9')
            freqs[chr]++;
    }
}

void  alg4::str::init_pq_node(Node_pq& pq, const unordered_map<char, int>& freqs)
{
    for (const auto& [chr, freq] : freqs)
        pq.push(new Node(chr, freq));
}

void alg4::str::init_tire(Node*& root, Node_pq pq)
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

//回溯生成每个字符的哈夫曼编码
void alg4::str::encode(unordered_map<char, string>& codes, Node* root, string& code)
{
    {
        if (root->isleaf()) {
            codes.insert({ root->chr_, code });
            return;
        }
        if (root->left_ != nullptr) {
            code.push_back('0');
            encode(codes, root->left_, code);
            code.pop_back();
        }
        if (root->right_ != nullptr) {
            code.push_back('1');
            encode(codes, root->right_, code);
            code.pop_back();
        }
    }
}

void alg4::str::reserve_code(const unordered_map<char, int>& freqs, const unordered_map<char, string>& codes, string & str)
{
    size_t bits = 0;
    for ( auto& [chr, freq] : freqs)
    {
        auto code = codes.find(chr)->second;
        bits += freq * code.size();
    }
    str.reserve(bits);
}


void alg4::str::init_data(ifstream& ifs, string& str, unordered_map<char, string>& codes)
{
    char chr;
    while (ifs.get(chr))
    {
        if (auto itr = codes.find(chr); itr != codes.end())
            str.append(itr->second);
    }

}