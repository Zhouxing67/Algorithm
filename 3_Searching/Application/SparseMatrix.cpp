#include <iostream>
#include "SparseMatrix.h" // 假设头文件名为 SparseMatrix.h

using namespace alg4::search;
int main()
{
    // 创建一个稀疏矩阵对象
    std::vector<std::vector<double>> matrixData = {
        {0.0, 2.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 5.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };

    SparseMatrix<double> sparseMatrix(matrixData, 0.0001); // 设置容差为0.0001

    // 输出稀疏矩阵的形状
    auto shape = sparseMatrix.shape();
    std::cout << "Sparse Matrix Shape: (" << shape.first << ", " << shape.second << ")\n";

    // 创建一个测试向量
    std::vector<double> vectorData = { 1.0, 2.0, 3.0, 4.0 };

    // 计算稀疏矩阵与向量的乘积
    std::vector<double> result = sparseMatrix * vectorData;

    // 输出结果
    std::cout << "Result of multiplication: ";
    for (double val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
