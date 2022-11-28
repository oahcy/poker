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

inline bool IsFlush(const PokerHand &pokerHand) {
  int suitCounts = 0;
  suitCounts =
      (pokerHand.hearts == 0 ? 0 : 1) + (pokerHand.clubs == 0 ? 0 : 1) +
      (pokerHand.spades == 0 ? 0 : 1) + (pokerHand.diamonds == 0 ? 0 : 1);
  return suitCounts == 1;
}