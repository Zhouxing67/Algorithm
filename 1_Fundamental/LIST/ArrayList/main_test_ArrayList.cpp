#include"ArrayList.h"
using alg4::List::ArrayList;
int main()
{
    ArrayList<int> myList;
    myList.insert(0, 0);
    myList.insert(1, 0);
    myList.insert(2, 1);
    myList.insert(3, 2);
    for (int i = 0; i < myList.len(); i++)
        std::cout << myList[i] << " ";

}