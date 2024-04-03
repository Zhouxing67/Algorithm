/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Majority.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhouX <zhouxing.joe@qq.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:36:28 by zhouX             #+#    #+#             */
/*   Updated: 2024/04/03 09:36:28 by zhouX            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAJORITY_INCLUDE_H
#define MAJORITY_INCLUDE_H

#include "../../base_include.h"

namespace alg4
{
    //摩尔投票， 选出出现频率大于1 / (n + 1)的n 个元素，如果这n个元素存在的话， 算法将给出正确答案
    class Majority {
    private:
        int* cnts_ = nullptr;
        int* majority_ = nullptr;

        void vote(const vector<int>& data, int n)
        {
            for (const auto& i : data)
            {
                size_t in_majority  = std::find(majority_, majority_ + n, i) - majority_;
                if (in_majority < n)
                {
                    cnts_[in_majority]++;
                    continue;
                }
                size_t cnt_zero = std::find(cnts_, cnts_ + n, 0) - cnts_;
                if (cnt_zero < n)
                {
                    majority_[cnt_zero] = i;
                    cnts_[cnt_zero]++;
                    continue;
                }
                for (int j = 0; j != n; j++)
                    cnts_[j]--;
            }
        }
    public:
        explicit Majority(const vector<int>& data, int n)
        {
            cnts_ = new int[n];
            majority_ = new int[n];
            memset(cnts_, 0, n * sizeof(int)); 
            memset(majority_, 0, n * sizeof(int));

            vote(data, n);
        }

        const int* get_majority() const { return majority_; }

        ~Majority()
        {
            delete[] majority_;
            delete[] cnts_;
        }
    };
}
#endif