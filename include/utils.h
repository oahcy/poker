#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include "texas.h"

template <class T>
void printVector(const std::vector<T> &v) {
    std::ostream_iterator<T> it(std::cout, " ");
    std::copy(v.begin(), v.end(), it);
    return;
}

inline
int GetOneCounts(uint16_t num) {
    int bitCounts = 0;
    while (num) {
        bitCounts++;
        num &= num - 1;
    };
    return bitCounts;
}

inline
uint16_t GetLastOneBit(uint16_t num) {
    uint16_t ret = 0;
    if (num) {
        ret = ((num ^ (num - 1)) + 1) >> 1; 
    }
    return ret;
}