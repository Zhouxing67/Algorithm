
#include <iostream>
#include "LinkStack.h"

int main()
{
    alg4::LinkStack<int> stack;

    std::cout << "Pushing elements onto the stack..." << std::endl;
    for (int i = 0; i < 5; ++i) {
        stack.push(i);
        std::cout << "Pushed: " << i << std::endl;
    }

    std::cout << "Top element: " << stack.top() << std::endl;

    std::cout << "Popping elements from the stack..." << std::endl;
    while (!stack.empty()) {
        std::cout << "Popped: " << stack.top() << std::endl;
        stack.pop();
    }

    return 0;
}
