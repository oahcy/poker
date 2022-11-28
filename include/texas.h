#pragma once

#include <string>

#define SUIT_DIAMONDS 1
#define SUIT_CLUBS 2 //梅花
#define SUIT_HEARTS 3
#define SUIT_SPADES 4 //黑桃

#define GET_SUIT(x) (x >> 8)
#define GET_RANK(x) ((x & 0xff) - 2)
#define GET_RAND_BIT(x) (1 << GET_RANK(x))

#define HAND_COUNTS 5
#define SUIT_COUNTS 4
#define RANK_COUNTS 13

enum HandType {
    RoyalStraightFlush = 1,
    StraightFlush,
    Quads,
    FullHouse,
    Flush,
    Straight,
    Trips,
    TwoPair,
    Pair,
    NoPair,
    Joker,
    Undefined,
};

typedef struct PokerHandS{
    PokerHandS():diamonds(0),clubs(0),hearts(0),spades(0) {}
    uint16_t diamonds;
    uint16_t clubs;
    uint16_t hearts;
    uint16_t spades;
}PokerHand, *pPokerHand;

std::string
helloWorld();
std::string sort(const std::vector<int>& input);
HandType GetHandType(const std::vector<int> &hexHands);
HandType GetJokerHandType(const std::vector<int>& input);
HandType GetTexasHandType(const std::vector<int>& self, const std::vector<int>& board);
int GetWinRateAtRiver(const std::vector<int>& self, const std::vector<int>& board);