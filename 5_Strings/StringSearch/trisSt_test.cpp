#include <iostream>
#include "TrisSt.h"

using namespace std;
using namespace alg4::str;

int main()
{
    // 创建一个 TrisSt 实例，用于测试
    TrisSt<int> trisSt;

    // 插入一些键值对
    trisSt.put("app", 5);
    trisSt.put("apple", 5);
    trisSt.put("apply", 5);
    trisSt.put("banana", 10);
    trisSt.put("orange", 15);
   

    // 测试获取键值对

    cout << "Size of TrisSt: " << trisSt.size() << endl;
    // 测试获取键值对
    trisSt.del("banana");
    cout << "Size of TrisSt: " << trisSt.size() << endl;

    cout << *trisSt.get("app") << endl;
//    cout << *trisSt.get("appl") << endl;
    cout << *trisSt.get("apply") << endl;
    cout << *trisSt.get("orange") << endl;


    auto valPtr = trisSt.get("banana");
    if (valPtr) cout << "Value for key 'banana': " << *valPtr << endl;
    else  cout << "Key 'banana' not found." << endl;
    
    
    auto res = trisSt.keysWithPrefix("app");
    for (size_t i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    
    return 0;
}
