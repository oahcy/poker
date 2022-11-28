#pragma once
#include <string>

#define RANK_BIT_MAP_2   0b0000000000001
#define RANK_BIT_MAP_3   0b0000000000010
#define RANK_BIT_MAP_4   0b0000000000100
#define RANK_BIT_MAP_5   0b0000000001000
#define RANK_BIT_MAP_6   0b0000000010000
#define RANK_BIT_MAP_7   0b0000000100000
#define RANK_BIT_MAP_8   0b0000001000000
#define RANK_BIT_MAP_9   0b0000010000000
#define RANK_BIT_MAP_10  0b0000100000000
#define RANK_BIT_MAP_J   0b0001000000000
#define RANK_BIT_MAP_Q   0b0010000000000
#define RANK_BIT_MAP_K   0b0100000000000
#define RANK_BIT_MAP_A   0b1000000000000

#define TYPE_BABY_STRAIGHT 0b1000000001111
#define TYPE_ROYAL_STRAIGHT 0b1111100000000

std::string ConvertToString(int hexHand);
std::string ConvertTypeToString(HandType t);
int ConvertHand(PokerHand& hand, const std::vector<int> &hexHands);
void printPoker(const std::vector<int> &v);