#include "BitTree.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
int main()
{
    vector<int> arr = {3, 2, -1, 6, 5, 4, -3, 3, 7};
    int n = arr.size();
    
    alg4::BitTree bit(n);
    for (int i = 0; i < n; i++) {
        bit.update(i + 1, arr[i]);  // 注意树状数组的索引从 1 开始
    }

    // 查询区间 [2, 6] 的累加和
    int l = 2, r = 7;
    int sum_lr = bit.query(r) - bit.query(l - 1);

    cout << "Sum of interval [" << l << ", " << r << "] is: " << sum_lr << endl;

    return 0;
}