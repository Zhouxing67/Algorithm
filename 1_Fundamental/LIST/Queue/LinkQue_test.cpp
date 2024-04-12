#include <iostream>
#include "LinkQue.h"
using namespace alg4;
int main()
{
    alg4::list::LinkQue<int> queue;

    std::cout << "Pushing elements onto the queue..." << std::endl;
    for (int i = 0; i < 5; ++i) {
        queue.push(i);
        std::cout << "Pushed: " << i << std::endl;
    }

    std::cout << "Front element: " << queue.front() << std::endl;

    std::cout << "Popping elements from the queue..." << std::endl;
    while (1) {
        std::cout << "Front element: " << queue.front() << std::endl;
        queue.pop();
    }

    return 0;
}
