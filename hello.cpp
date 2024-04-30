#include <iostream>
#include <vector>

std::vector<int> readByte(char Byte, size_t bitnum = 1)
{
    std::vector<int> vet;
    // 注意循环条件应该是 i >= bitnum，而不是 i >= 0，避免无限循环
    for (int i = 8 - bitnum; i >= 0; i -= bitnum) {
        // 取出从第 i 位开始的 bitnum 个比特
        int val = (Byte >> i) & ((1 << bitnum) - 1);
        vet.push_back(val);
    }
    return vet;
}

int main()
{
    char byte = 0b10101010; // 二进制表示的字节 10101010

    // 读取每个比特并存储在向量中
    std::vector<int> bits = readByte(byte, 1); // 每次读取2个比特

    // 输出向量中的比特值
    std::cout << "Bits read from byte:";
    for (int bit : bits) {
        std::cout << " " << bit;
    }
    std::cout << std::endl;

    return 0;
}
