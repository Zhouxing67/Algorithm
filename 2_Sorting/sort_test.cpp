#include"SimpleSort.h"
#include"MergeSort.h"
#include"QuickSort.h"
#include"HeapSort.h"

#include"Util_test_sort.h"
/*
    重载的函数无法通过函数名确定函数指针；
    这意味着如果一个函数被重载了， 则无法通过其函数名来直接初始化一个std::function对象；
    只能说有说法的

    比如说：下面有int版本的add和一个重载了double版本的add，
    int add(int a, int b);
    double add(double a, double b);

    那么对于类型为std::function<int(int, int)> f = add 的初始化无效，编译器会报错：

    “没有与参数列表匹配的构造函数 "std::function<_Res (_ArgTypes...)>::function [其中 _Res=int, _ArgTypes=<int, int>]" 实例C/C++(289)
    参数类型为: (<unknown-type>)”， unknown-type即表明编译器无法确定add的具体类型；

    解决方法：通过static_cast强制转换，还可以通过将其赋值到一个具体类型的函数指针上，使用这个指针初始化std::function，以下是这两种方式的例子
    方式一：    std::function<int(int, int)> f(static_cast<int(*)(int, int)>(add));

    方式二：    int (*func_ptr)(int, int) = add; //这样居然能正确匹配到函数：int add(int a, int b);
                std::function<int(int, int)> f(func_ptr);
 */

using namespace alg4::sort;
using namespace alg4::util;
using namespace alg4;
int main()
{
    const int len = 15000;
    int* randow_ = new int[len];
    RangeType<int> range{ -1000, 1000};

    sort_util::sort_test(randow_, range, sortFunc<int>(SimpleSort::shell_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(SimpleSort::insert_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(SimpleSort::select_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(SimpleSort::bubble_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(MergeSort::merge_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(QuickSort::quick_sort<int>), len);
    
    sort_util::sort_test(randow_, range, sortFunc<int>(QuickSort::quick3way_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(HeapSort::heap_sort<int>), len);

    delete randow_;
}
