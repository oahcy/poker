#pragma once
#include <string>

#define TYPE_BABY_STRAIGHT 0b1000000001111
#define TYPE_ROYAL_STRAIGHT 0b1111100000000

std::string ConvertToString(int hexHand);
std::string ConvertTypeToString(HandType t);
int ConvertHand(PokerHand& hand, const std::vector<int> &hexHands);
void printPoker(const std::vector<int> &v);