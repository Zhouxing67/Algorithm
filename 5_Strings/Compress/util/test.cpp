#include <iostream>
#include <fstream>
#include "StreamBitIn.h" // Assuming StreamBitIn.h contains the class declaration
#include "StreamBitOut.h"

int main()
{
    // Open a file for reading
    std::ofstream ofs("a.txt");
    ofs << '\0';
    alg4::util::StreamBitOut bw(ofs);
    bw.writeOneBit(0);
    bw.writeOneBit(0);
    bw.writeOneBit(1);
    bw.writeOneBit(1);
    bw.writeOneByte('a');//01100001
    bw.writeOneBit(0);
    bw.writeOneBit(0);
    bw.writeOneBit(0);
    bw.writeOneBit(1);
    bw.close();
    ofs.close();

    std::ifstream ifs("a.txt");
    alg4::util::StreamBitIn br(ifs);
    bool bit;
   for(int i = 0; i < 16; i++)
    {
        br.readBit(bit);
        std::cout << bit << " ";
    }
    

}
