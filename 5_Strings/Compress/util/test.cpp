#include <iostream>
#include <fstream>
#include "StreamBitIn.h" // Assuming StreamBitIn.h contains the class declaration
#include "StreamBitOut.h"
//g++ test.cpp StreamBItIn.cpp StreamBitOut.cpp -o test
int main(int argc, char* argv[])
{
    // Open a file for reading

    std::ifstream ifs(argv[1]);
    alg4::util::StreamBitIn br(ifs);
    bool bit;
    char byte;
   
    std::cout << std::endl;
    while (1)
    //for(int i = 0; i< 64; i++)
    {
        if(br.readBit(bit))
            std::cout << bit << " ";
        else
            break;
    }

    std::cout <<std:: endl;
    std::ofstream ofs("write.txt");
    alg4::util::StreamBitOut bw(ofs);

    bw.writeOneBit(1);
    bw.writeOneBit(0);
    bw.writeOneBit(1);
    bw.writeOneBit(0);
    bw.writeOneBit(1);

    bw.close();
    ofs.close();
    std::ifstream ifs2("write.txt");
    alg4::util::StreamBitIn br2(ifs2);
    while(br2.readBit(bit))
        std::cout << bit << " ";
}
