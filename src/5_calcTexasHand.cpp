#include "texas.h"
#include "5_calcTexasHand.h"
#include "3_calcPoker.h"
#include "utils.h"

#include <vector>
#include <map>

uint16_t GetTypeValue(HandType t) {
    if ((t <= HandType::NoPair) && (t >= HandType::RoyalStraightFlush)) {
        return HandType::NoPair - t;
    } else {
        assert(false);
        return 0;
    }
}

bool IsNoPair(const std::vector<int> &hands) {
  PokerHand pokerHand;
  if (0 == ConvertHand(pokerHand, hands)) {
    uint16_t allRankComb = pokerHand.hearts | pokerHand.clubs | pokerHand.spades | pokerHand.diamonds;
    int allRankCombCounts = GetOneCounts(allRankComb);
    return (allRankCombCounts == hands.size());
  }
  return false;
}

bool cmp(std::pair<int, int>& a,
         std::pair<int, int>& b) {
    if (a.second > b.second) {
      return true;
    } else if (a.second == b.second) {
      return (a.first > b.first);
    }
    return false;
}

uint32_t GetHandValue(const std::vector<int> &hands) {
    uint32_t value = 0;
    auto handType = GetHandType(hands);
    auto handTypeValue = GetTypeValue(handType);
    std::vector<int> rankVec;
    for (const auto &hand : hands) {
      rankVec.push_back((GET_RANK(hand) & 0xf));
    }
    if (IsNoPair(hands)) {
      std::sort(rankVec.begin(), rankVec.end(), std::greater<int>());
      //a2345 is smallest straight
      if ((rankVec[0] == 12) && (rankVec[1] == 3) && (rankVec[2] == 2) && (rankVec[3] == 1) && (rankVec[4] == 0)) {
        rankVec[0] = 0;
      }
      value = handTypeValue;
      for (const auto &hand : rankVec) {
        value <<= 4;
        value = value | hand;
      }
      return value;
    }
    //calc pair
    std::map<int, int> mapSortHands;
    for (const auto &hand : rankVec) {
      auto findIter = mapSortHands.find(hand);
      if (findIter == mapSortHands.end()) {
        mapSortHands.insert(std::pair<int, int>(hand, 1));
      } else {
        findIter->second++;
      }
    }

    std::vector<std::pair<int, int>> sortMapVec;
    for (auto& it : mapSortHands) {
        sortMapVec.push_back(it);
    }
    std::sort(sortMapVec.begin(), sortMapVec.end(), cmp);
    value = handTypeValue;
    for (const auto &handPair : sortMapVec) {
      value <<= 4;
      value = value | handPair.first;
    }
    value <<= (4 * (HAND_COUNTS - sortMapVec.size()));
    return value;
}

std::vector<std::vector<int>> combination(std::vector<int> arr, int num) {
  std::vector<std::vector<int>> r;
  std::function<void(std::vector<int>, std::vector<int>, int)> func = [&r, &func](std::vector<int> t, std::vector<int> a, int n) {
    if (n == 0) {
      return r.push_back(t);
    }
    for (int i = 0, l = a.size(); i <= l - n; i++) {
      std::vector<int> leftArr = a;
      leftArr.erase(leftArr.begin(), leftArr.begin() + i + 1);
      auto temp = t;
      temp.push_back(a[i]);
      func(temp, leftArr, n - 1);
    }
  };
  std::vector<int> t;
  func(t, arr, num);
  return r;
}

bool GetTexasMaxHands(const std::vector<int> &allHands,
                      std::vector<int> &maxHands, uint32_t &maxValue) {
  std::vector<int> orders = {0, 1, 2, 3, 4, 5, 6};
  assert(allHands.size() == 7);
  assert(HAND_COUNTS == 5);
  static std::vector<std::vector<int>> allHandComb = combination(orders, HAND_COUNTS);

  uint32_t tempMaxValue = 0;
  std::vector<int> tempMaxHands;
  for (const auto &comb : allHandComb) {
    std::vector<int> testHand;
    for (int i = 0; i < HAND_COUNTS; i++) {
      testHand.push_back(allHands[comb[i]]);
    }
    auto handValue = GetHandValue(testHand);
    if (handValue > tempMaxValue) {
      tempMaxValue = handValue;
      tempMaxHands = testHand;
    }
  }
  maxValue = tempMaxValue;
  maxHands = tempMaxHands;
  return true;
}

HandType GetTexasHandType(const std::vector<int> &self,
                          const std::vector<int> &board) {
  std::vector<int> allHands = self;
  assert((self.size() == 2));
  assert((board.size() == 5));
  allHands.insert(allHands.end(), board.begin(), board.end());
  std::vector<int> maxHands;
  uint32_t maxValue = 0;
  GetTexasMaxHands(allHands, maxHands, maxValue);
  if (maxValue > 0) {
    return GetHandType(maxHands);
  }
  assert(false);
  return HandType::Undefined;
}
