#ifndef SPARSEMATRIX_INCLUDE_H
#define SPARSEMATRIX_INCLUDE_H

#include <unordered_map>
#include <vector>
#include <cmath>

using std::vector;
using std::unordered_map;

namespace alg4::search
{
    template<typename T>
    class SparseMatrix
    {
    private:
        vector<unordered_map<size_t, T>> data_;
        size_t row_;
        size_t col_;
    public:
        SparseMatrix(const vector<vector<T>>& vet, T tolerance)
        {
            if (vet.size() == 0)
                throw std::invalid_argument("empty vector is invalid");
            row_ = vet.size();
            col_ = vet[0].size();

            data_.resize(row_, unordered_map<size_t, T>());
            for (size_t i = 0; i < vet.size(); i++) {
                for (size_t j = 0; j < vet[0].size(); j++) {
                    T cur = vet[i][j];
                    if (cur > tolerance || cur < -1 * tolerance) {
                        data_[i][j] = vet[i][j];
                    }
                }
            }

        }

        const size_t row() const { return row_; }
        const size_t col() const { return col_; }
        const vector<unordered_map<size_t, T>>& data() const { return data_; }
        const std::pair<size_t, size_t> shape() const { return std::make_pair(row_, col_); }
    };

    
    template<typename T>
    vector<T> operator*(const SparseMatrix<T>mat, const vector<T>& vet)
    {
        if (vet.size() != mat.col())
            throw std::invalid_argument("invalid vector for mutiply");
        vector<T> res;
        for (size_t j = 0; j < mat.row(); j++) {
            auto umap = mat.data()[j];
            T tmp = 0;
            if (umap.size() != 0)
                for (size_t i = 0; i < mat.col(); i++) {
                    if (umap.find(i) != umap.end())
                        tmp += vet[i] * umap[i];
                }
            res.push_back(tmp);
        }
        return res;
    }



}


#endif