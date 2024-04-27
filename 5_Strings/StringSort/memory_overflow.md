# C/C++ 数组越界问题

### Profile

C/C++ 允许直接访问内存， 这使得我们可以更好的掌握机器，与此同时，**C/C++**对内存的的孱弱的保护能力也会使得程序异常，比如它们对于数组越界的问题似乎都无可奈何



### 内存区域

一般来说数组可以分配在 **全局变量区，栈区，*堆区***（不讨论静态数组， 因为目前还不清楚）

### 越界读

对这三个区域的**轻微越界读**都不会被察觉，当然过分越界会导致<font color=red>Segmentation fault</font>

```c++
#include <iostream>
using namespace std;

constexpr size_t len = 100;

int global_array[len] = { 999 };
int main()
{
    int stack_array[len] = { 999 };

    int* heap_array = new int[len] {999};

    int pos = 100;
    cout << "overflow global_array :" << global_array[pos] << endl;
    cout << "overflow stack_array :" << stack_array[pos] << endl;
    cout << "overflow heap_array :" << heap_array[pos] << endl;

    delete[] heap_array;
}
```

以下是程序的运行结果

```
overflow global_array :0
overflow stack_array :8
overflow heap_array :-1414812757
```

当我们继续调整越界的位置，如令pos = 15000: 程序将会因<font color=red>Segmentation fault</font>而crash。



### 越界写

同样的，对这三个区域的**轻微越界写**也都不会被察觉，当然，过分越界会导致<font color=red>Segmentation fault</font>

```c++
#include <iostream>
using namespace std;

constexpr size_t len = 100;

int global_array[len] = { 999 };
int main()
{
    int stack_array[len] = { 999 };

    int* heap_array = new int[len] {999};

    int pos = 100;
    global_array[pos] = 1000;
    stack_array[pos] = 1000;
    heap_array[pos] = 1000;
    
    cout << "overflow global_array :" << global_array[pos] << endl;
    cout << "overflow stack_array :" << stack_array[pos] << endl;
    cout << "overflow heap_array :" << heap_array[pos] << endl; 

    //delete[] heap_array;
}
```

以下为运行结果：

```c++
overflow global_array :1000
overflow stack_array :1000
overflow heap_array :1000
```

同样的，当我们继续调整越界的位置，令pos = 15000: 程序将会因<font color=red>Segmentation fault</font>而crash。



你可能注意到越界写的代码的最后一行释放堆内存的代码被注释了，这就是我们将讨论的下一个主题

### 内存区域损坏

对堆内存的越界写会导致所分配的内存被损坏，导致在释放内存时， 程序将被操作系统中断

```c++
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
```

运行后，程序将会应为PAUSE暂停，以下是gdb显示的调用堆栈的信息

```c++
ntdll.dll!ntdll!RtlRegisterSecureMemoryCacheCallback (未知源:0)
ntdll.dll!ntdll!RtlZeroHeap (未知源:0)
ntdll.dll!ntdll!EtwLogTraceEvent (未知源:0)
ntdll.dll!ntdll!RtlRegisterSecureMemoryCacheCallback (未知源:0)
ntdll.dll!ntdll!EtwLogTraceEvent (未知源:0)
ntdll.dll!ntdll!RtlGetCurrentServiceSessionId (未知源:0)
ntdll.dll!ntdll!RtlFreeHeap (未知源:0)
msvcrt.dll!msvcrt!free (未知源:0)
main() (c:\Codefield\C\C++\Algorithm\hello.cpp:15)
```

堆栈跟踪信息，表明程序在执行 `free`函数（标准 C 运行时库（CRT）函数， Windows下由msvcrt.dll提供），即回收动态内存时发生了错误

### 总结

==C/C++中， 对内存的轻微越界访问不会被留意。而对此类越界访问的忽视，将导致程序异常。同时这类bug会难以调试, 因为越界访问的概率较低，且一般不会被发现。 所以会出现程序会一直运行良好，而后突然崩溃。==