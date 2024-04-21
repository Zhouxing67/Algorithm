#include <iostream>
#include "Prime_num.h"

int main()
{
    try {
        // 创建 PrimeNum 实例，求解 100 以内的所有素数
        alg4::Prime_num primeNum(100);

        // 获取素数序列
        const auto& primes = primeNum.get_primers();

        // 输出素数序列
        std::cout << "Prime numbers up to 100: ";
        for (int prime : primes) {
            std::cout << prime << " ";
        }
        std::cout << std::endl;

        // 检查某些数是否为素数
        std::cout << "Is 17 a prime number? " << (primeNum.is_primer(17) ? "Yes" : "No") << std::endl;
        std::cout << "Is 25 a prime number? " << (primeNum.is_primer(25) ? "Yes" : "No") << std::endl;
        std::cout << "Is 97 a prime number? " << (primeNum.is_primer(97) ? "Yes" : "No") << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }

    return 0;
}
