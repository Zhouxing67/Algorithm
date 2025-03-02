#ifndef BUDDY_SYS_H
#define BUDDY_SYS_H
#include <stdint.h>
#include <vector>
using std::vector;
namespace alg4
{
    
    class buddy_sys {
    private:
        uint16_t size_;
        uint16_t spilt(uint16_t size);
        static buddy_sys* instance_;
        vector<vector<uint16_t>> map;
    public:
        buddy_sys(uint16_t size) : size_(size){}
        uint16_t malloc(uint16_t size);
        void free(uint16_t addr, uint16_t size);
    };
}
#endif