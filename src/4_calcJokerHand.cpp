#include "texas.h"
#include "4_calcJokerHand.h"
#include "3_calcPoker.h"
#include "utils.h"

#include <vector>

uint16_t GetJokerMaxStraight(uint16_t handBits) {
    uint16_t straightMask = 0;
    std::vector<uint16_t> straightMasks = {
        0b1111100000000,
        0b0111110000000,
        0b0011111000000,
        0b0001111100000,
        0b0000111110000,
        0b0000011111000,
        0b0000001111100,
        0b0000000111110,
        0b0000000011111,
        0b1000000001111, //a2345

    };
    //get the max straight
    for (const auto &mask : straightMasks) {
        if ((handBits | mask) == mask) {
            straightMask = mask;
            break;
        }
    }
    return straightMask;
}

HandType GetJokerHandType(const std::vector<int>& input) {
    PokerHand pokerHand;
    HandType t = GetHandType(input);
    if (t != HandType::Joker) {
        return t;
    }
    int jokerCounts = ConvertHand(pokerHand, input);
    assert((jokerCounts == 1) || (jokerCounts == 2));
    bool isFlush = IsFlush(pokerHand);
    uint16_t allRankComb = pokerHand.hearts | pokerHand.clubs | pokerHand.spades | pokerHand.diamonds;
    int allRankCombCounts = GetOneCounts(allRankComb);
    uint16_t straightMask = 0;

    //一个癞子
    if (jokerCounts == 1) {
        //may be straight
        if (allRankCombCounts + 1 == HAND_COUNTS) {
            straightMask = GetJokerMaxStraight(allRankComb);
        }
        //皇家同花顺 / 同花顺
        if (straightMask != 0) {
          if (isFlush) {
            if (0b1111100000000 == straightMask) {
              return HandType::RoyalStraightFlush;
            }
            return HandType::StraightFlush;
          }
        }

        //金刚
        if (allRankCombCounts == 1) {
          return HandType::Quads;
        }
        if (allRankCombCounts == 2) {
          bool isQuads = false;
          // 有三个一样
          do {
            if (pokerHand.clubs & pokerHand.diamonds & pokerHand.hearts) {
              isQuads = true;
              break;
            }
            if (pokerHand.spades & pokerHand.diamonds & pokerHand.hearts) {
              isQuads = true;
              break;
            }
            if (pokerHand.clubs & pokerHand.spades & pokerHand.hearts) {
              isQuads = true;
              break;
            }
            if (pokerHand.clubs & pokerHand.diamonds & pokerHand.spades) {
              isQuads = true;
              break;
            }
          } while (false);

          if (isQuads) {
            return HandType::Quads;
          }
          //有2对 组成葫芦
          return HandType::FullHouse;
        }

        if (isFlush) {
            return HandType::Flush;
        }
        if (0 != straightMask) {
            return HandType::Straight;
        }
        //有一对 组成三条
        if (allRankCombCounts == 3) {
            return HandType::Trips;
        }
        //啥也没有 可以组成一对
        return HandType::Pair;
    }
    
    //2个赖子
    if (jokerCounts == 2) {
        //may be straight
        if (allRankCombCounts + 2 == HAND_COUNTS) {
            straightMask = GetJokerMaxStraight(allRankComb);
        }
        //皇家同花顺 / 同花顺
        if (straightMask != 0) {
          if (isFlush) {
            if (0b1111100000000 == straightMask) {
              return HandType::RoyalStraightFlush;
            }
            return HandType::StraightFlush;
          }
        }

        //金刚 
        if (allRankCombCounts <= 2) {
            return HandType::Quads;
        }
        //有一对就可以组成金刚，所以没有葫芦了。
        //同花
        if (isFlush) {
            return HandType::Flush;
        }
        if (0 != straightMask) {
            return HandType::Straight;
        }
        //最差是3条
        return HandType::Trips;
    }
    //不会走到这里
    assert(false);
    return t;
}