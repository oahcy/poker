#include "texas.h"
#include "utils.h"
#include "3_calcPoker.h"

std::string ConvertTypeToString(HandType t) {
  std::vector<std::string> types = {"RoyalStraightFlush", "StraightFlush", \
  "Quads", "FullHouse", "Flush", "Straight", "Trips", "TwoPair", "Pair", "NoPair", "Joker"};
  return types[static_cast<int>(t) - 1];
}

std::string ConvertToString(int hexHand) {
  std::vector<std::string> suits = {"diamonds", "clubs", "hearts", "spade", "queue", "king"};
  char ranks[] = "JQKA**";
  std::string result;
  int suit = GET_SUIT(hexHand);
  uint16_t rank = GET_RANK(hexHand);
  if (((suit << 8) | rank) == (hexHand - 2)) {
    result += suits[suit - 1];
    result += ":";
    if (rank <= 7) {
      result += ('2' + rank);
    } else if (rank == 8) {
      result += "10";
    } else if ((rank >= 9) && (rank <= 15)) {
      result += ranks[(rank - 9)];
    }
  }
  return result;
}

void printPoker(const std::vector<int> &v) {
    for (auto const &x : v) {
        std::string s = ConvertToString(x);
        if (!s.empty()) {
            std::cout << s << " ";
        }else {
            std::cout << x << " ";
        }
    }
}

bool ConvertHand(PokerHand& hand, int hexHand) {
    int suit = GET_SUIT(hexHand);
    uint16_t rank = GET_RAND_BIT(hexHand);
    bool ret = true;
    switch (suit)
    {
    case SUIT_DIAMONDS:
        hand.diamonds |= rank;
        break;
    case SUIT_CLUBS:
        hand.clubs |= rank;
        break;
    case SUIT_HEARTS:
        hand.hearts |= rank;
        break;
    case SUIT_SPADES:
        hand.spades |= rank;
        break;
    default:
        ret = false; //大小王
    }
    return ret;
}

int ConvertHand(PokerHand& hand, const std::vector<int> &hexHands) {
    int unConverts = 0;
    for (auto const &hexHand : hexHands) {
        if (!ConvertHand(hand, hexHand)) {
            unConverts ++;
        }
    }
    return unConverts;
}

HandType GetHandType(const PokerHand &pokerHand) {
    uint16_t allRankComb = pokerHand.hearts | pokerHand.clubs | pokerHand.spades | pokerHand.diamonds;
    uint16_t allRankSame = pokerHand.hearts & pokerHand.clubs & pokerHand.spades & pokerHand.diamonds;
    int allRankCombCounts = GetOneCounts(allRankComb);
    //顺子
    bool isStraight = (allRankCombCounts == 5) && (GetOneCounts(allRankComb + GetLastOneBit(allRankComb)) == 1);
    //a2345
    if (!isStraight && ((allRankComb & TYPE_BABY_STRAIGHT) == TYPE_BABY_STRAIGHT)) {
        isStraight = true;
    }
    //同花
    bool isFlush = IsFlush(pokerHand);

    //皇家同花顺 / 同花顺
    if (isStraight && isFlush) {
        if ((allRankComb & TYPE_ROYAL_STRAIGHT) == TYPE_ROYAL_STRAIGHT) {
            return HandType::RoyalStraightFlush;
        }
        return HandType::StraightFlush;
    }

    //金刚 / 葫芦
    if (allRankCombCounts == 2) {
        if (allRankSame != 0) {
            return HandType::Quads;
        }
        return HandType::FullHouse;
    }

    //同花
    if (isFlush) {
        return HandType::Flush;
    }

    //顺子
    if (isStraight) {
        return HandType::Straight;
    }

    //三条
    if (allRankCombCounts == 3) {
        bool isTrips = false;
        do {
            if (pokerHand.clubs & pokerHand.diamonds & pokerHand.hearts) {
                isTrips = true;
                break;
            }
            if (pokerHand.spades & pokerHand.diamonds & pokerHand.hearts) {
                isTrips = true;
                break;
            }
            if (pokerHand.clubs & pokerHand.spades & pokerHand.hearts) {
                isTrips = true;
                break;
            }
            if (pokerHand.clubs & pokerHand.diamonds & pokerHand.spades) {
                isTrips = true;
                break;
            }
        }while(false);

        if (isTrips) {
            return HandType::Trips;
        }
        //对子
        return HandType::TwoPair;
    }

    if (allRankCombCounts == 4) {
        return HandType::Pair;
    }

    return HandType::NoPair;
}

HandType GetHandType(const std::vector<int> &hexHands) {
  PokerHand pokerHand;
  if (ConvertHand(pokerHand, hexHands) == 0) {
    return GetHandType(pokerHand);
  }
  return HandType::Joker;
}