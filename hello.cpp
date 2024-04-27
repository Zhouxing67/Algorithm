#include <iostream>
using namespace std;

constexpr size_t len = 100;

int main()
{

    int* heap_array = new int[len] {999};

    int pos = 100;
    heap_array[pos] = 1000;
    cout << "overflow heap_array :" << heap_array[pos] << endl;

    delete[] heap_array;
}
/* int global_array[len] = { 999 };
int stack_array[len] = { 999 }; */

/*global_array[pos] = 1000;
    stack_array[pos] = 1000; */

    /* cout << "overflow global_array :" << global_array[pos] << endl;
    cout << "overflow stack_array :" << stack_array[pos] << endl; */