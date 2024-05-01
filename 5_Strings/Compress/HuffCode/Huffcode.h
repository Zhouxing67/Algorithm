#ifndef HUFF_CODE_H
#define HUFF_CODE_H
#include "data.h"
#include "Node.h"
#include "../util.h"

using alg4::util::StreamBitIn;
using alg4::util::StreamBitOut;

namespace alg4::str
{
    void com(const string& data, const string& file)
    {
        unordered_map<char, int> char_freq;
        priority_queue<Node*> pq_node;
        size_t chr_Num = 0;
        init_char_freq(data, char_freq, chr_Num);
        init_
    }
    void compress(const string& data, const string& file, Node* root, const unordered_map<char, string>& codes, size_t chr_num)
    {
        ofstream ofs(file);
        ofs << chr_num;
        StreamBitOut bw(ofs);
        write_tire(root, bw);
        write_data(codes, bw, data);
        bw.close();
        ofs.close();
    }

    void expand(const string& file, const string & expand)
    {

        ifstream ifs(file);
        ofstream ofs(expand);
        StreamBitIn br(ifs);
        StreamBitOut bw(ofs);
        Node* root = read_tire(br);

        size_t chr_num;
        ifs >> chr_num;
        bool bit;
        while(chr_num--) {
            Node* node = root;
            bool unfinshed = 1;
            while (!node->isleaf() && (unfinshed = br.readBit(bit))) {
                if (bit)
                    node = node->right_;
                else
                    node = node->left_;
            }
            if(unfinshed)
                bw.writeOneByte(node->chr_);
        }

        ifs.close();
        bw.close();
        ofs.close();
        delete root;
    }

    //前序遍历， 将树写入压缩文件
    void write_tire(Node* node, StreamBitOut& bw)
    {
        
        if (!node->isleaf())
            bw.writeOneBit(0);
        else
        {
            bw.writeOneBit(1);
            bw.writeOneByte(node->chr_);
            return;
        }
        if (node->left_)
            write_tire(node->left_, bw);
        if (node->right_)
            write_tire(node->right_, bw);
    }

    //将哈夫曼编码写入压缩文件
    void write_data(const unordered_map<char, string>& codes, StreamBitOut& bw, const string& data)
    {
        char chr;
        ifstream ifs(data);
        if (!ifs)
            throw std::runtime_error("Open file failed");
        while (ifs) {
            ifs.get(chr);
            if (chr >= 'A' || chr <= 'z' || chr == ' ' || chr == '\n') {
                if (auto itr = codes.find(chr); itr != codes.end())
                {
                    string code = itr->second;
                    for (const auto chr : code)
                        if (chr == '0')
                            bw.writeOneBit(0);
                        else
                            bw.writeOneBit(1);
                }
            }
        }
    }

    //从压缩文件建立哈夫曼树
    Node* read_tire(StreamBitIn& br)
    {
        bool isleaf;
        char byte;
        br.readBit(isleaf);

        if (isleaf) {
            br.readByte(byte);
            return new Node(byte, -1);
        }
        else 
            return new Node(read_tire(br), read_tire(br), -1);
    }
}



#endif