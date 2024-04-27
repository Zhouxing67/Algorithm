#ifndef QUICK3WAYSTRING_INCLUDE_H
#define QUICK3WAYSTRING_INCLUDE_H

#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace alg4::str
{
    class Quick3WayString
    {
    public:
        static void quick3WayString_sort(vector<string>& arr)
        {
            q3sort(arr, 0, arr.size() - 1, 0);
        }
    private:
        static int charToIndex(const std::string &str, int pos)
        {
           // std::cout << str << std::endl;
            if (pos >= (int)str.size())
                return  -1;
            return str.at(pos);
        }
        static void swap(vector<string>& a, int i, int j)
        {
            string tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
        static void q3sort(vector<string> &arr, int lo, int hi, int d)
        {
            if (lo >= hi)
                return;

            int lt = lo, i = lo + 1, gt = hi;

            auto pivot = charToIndex(arr[lo], d);
            while (i <= gt) {
                auto cur = charToIndex(arr[i], d);
                if (cur < pivot)
                    swap(arr, i++, lt++);
                else if (pivot < cur)
                    swap(arr,gt--, i);
                else
                    i++;
            }

            q3sort(arr, lo, lt - 1, d);
            if (pivot >= 0)
                q3sort(arr, lt, gt, d + 1);
            q3sort(arr, gt + 1, hi, d);
        }
    
    };

}
#endif