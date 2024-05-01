#ifndef GENE_COMPRESS_H
#define GENE_COMPRESS_H
#include <fstream>
#include "../util.h"
#include <bitset>
#include <unordered_map>

using std::bitset;
using std::ifstream;
using std::ofstream;
using std::unordered_map;
namespace alg4::str
{
    using alg4::util::StreamBitOut;
    using alg4::util::readByte;

    const unordered_map<char, bitset<2>> Serialization{
        {'A', bitset<2>(0)},
        {'C', bitset<2>(1)},
        {'G', bitset<2>(2)},
        {'T', bitset<2>(3)}
    };

    const unordered_map<int, char> deSerialization{
        {0, 'A'}, {1, 'C'}, {2, 'G'}, {3, 'T'}
    };

    class GeneCompress {
    private:
        size_t len_ = 0;
        string data_;
        string compressfile_;
    public:
        GeneCompress(const string &data, const string &compressfile) : data_(data), compressfile_(compressfile)
        { }
        void compress()
        {
            ifstream ifs(data_);
            if (!ifs)
                throw std::invalid_argument("Oringal data is not existed");
            ofstream ofs(compressfile_, std::ios::binary);

            StreamBitOut bw(ofs);
            while (ifs) {
                char nucleobase;
                ifs.get(nucleobase);
                //ifs >> nucleobase;
                bitset<2> bits = Serialization.find(nucleobase)->second;
                bw.writeOneBit(bits[1]);
                bw.writeOneBit(bits[0]);
                len_++;
            }
            len_--;
            ifs.close();
            ofs.close();
        }

        void expand(string filename)
        {
            ifstream ifs(compressfile_);
            ofstream ofs(filename);

            if (!ifs)
                throw std::invalid_argument("compress file  is not existed!");
            while (ifs)
            {
                char byte;
                ifs.get(byte);
                vector<char> nucleobase = readByte(byte, 2);
                for (size_t i = 0; i < nucleobase.size() && len_; i++)
                {
                    len_--;
                    ofs << deSerialization.find(nucleobase[i])->second;
                }
                if (len_ == 0)
                    break;
            }
            ifs.close();
            ofs.close();

        }
    };
}
#endif 