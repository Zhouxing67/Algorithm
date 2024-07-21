#include <iostream>
#include "data.h"
#include "Huffcode.h"
#include "Node.h"

using namespace std;
using namespace alg4::str;

void display();

unordered_map<char, int> ferq_;
Node_pq pq_;
unordered_map<char, string> codes_;
Node* root_ = nullptr;
int zeros_;
string file_name("./data/data.txt");

int main(int argc, char* argv[])
{
    display();
    string code;
    string data;
    ifstream ifs(file_name);
    if (!ifs.is_open())
        throw runtime_error("File open failed");
    
    init_char_freq(ifs, ferq_);
    ifs.close();
    ifs.open(file_name);

    init_pq_node(pq_, ferq_);
    init_tire(root_, pq_);
    encode(codes_, root_, code);
    init_data(ifs, data, codes_);

    compress(data, zeros_);
    expand(zeros_, root_);

    ifs.close();
    return 0;
}

void display()
{
    cout << "\n\n";
    cout << "******************************************************************" << endl;
    cout << "C++标准为C++17,所有的文件名都硬编码到源码," << '\n'
         << "待压缩文本文件为data目录下的data.txt文件," << '\n'
         << "生成的压缩文件为data目录下的compress.huf文件" << '\n'
         << "程序逻辑为会压缩一次源文件，同时解压一次压缩文件，" << '\n' 
         << "运行run.bat,编译运行程序，同时比较原文件和解压后的文件的区别" << endl;
    cout << "******************************************************************" << endl;

}