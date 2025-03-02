#include "Huffcode.h"
using alg4::str::Node;

namespace
{
    const string huf_file = "./data/compress.huf";

    char to_byte(string&& str)
    {
        int byte = 0;
        for (int weight = 1, i = str.size() - 1; i >= 0; i--, weight *= 2) {
            byte += (str[i] - '0') * weight;
        }
        return byte;
    }

    void to_code(char byte, std::string& code)
    {
        code.resize(8);  // 确保字符串有足够的长度
        for (int i = 7; i >= 0; --i) {
            code[7 - i] = ((byte >> i) & 1) ? '1' : '0';
        }
    }
}



void alg4::str::compress(const string& data, int& zeros)
{
    ofstream ofs(huf_file);
    int pre = 0, size, reminder;
    for (; pre < data.size(); pre += 8) {
        reminder = data.size() - pre;
        size = reminder > 8 ? 8 : reminder;
        char byte = to_byte(data.substr(pre, size));
        ofs.put(byte);
    }
    zeros = 8 - reminder;
    ofs.close();
}

void alg4::str::expand(int zeros, Node* tie_root, const string& filename)
{
    ifstream ifs(huf_file);
    std::string data;
    char byte;
    std::string code;

    /* while (ifs) {
        ifs.get(byte);
        //这种写法，ifs.get(byte)读取失败后后续代码依然会执行，导致data多写入一个code
        to_code(byte, code);
        if (ifs.peek() == EOF) {
            code = code.substr(zeros);
        }
        data += code;
    }
    */
    while (ifs.get(byte)) {
        to_code(byte, code);
        if (ifs.peek() == EOF) {
            code = code.substr(zeros); // 处理最后一个字节的零填充
        }
        data += code;
    }

    ofstream ofs(filename);
    Node* cur = tie_root;
    for (const auto& bit : data) {
        if (bit == '0')
            cur = cur->left_;
        else
            cur = cur->right_;
        if (cur->isleaf()) {
            ofs.put(cur->chr_);
            cur = tie_root;
        }
    }

    ofs.close();
    ifs.close();
}
