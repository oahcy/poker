#include "texas.h"
#include "5_calcTexasHand.h"

#include <vector>

uint16_t GetTypeValue(HandType t) {
    if ((t <= HandType::NoPair) && (t >= HandType::RoyalStraightFlush)) {
        return HandType::NoPair - t;
    } else {
        assert(false);
        return 0;
    }
}

uint32_t GetHandValue(const std::vector<int> &hands) {
    uint32_t value = 0;
    auto handType = GetHandType(hands);
    auto handTypeValue = GetTypeValue(handType);
    auto sortHands = hands;
    std::sort(sortHands.begin(), sortHands.end(), std::greater<int>());
    value = handTypeValue;
    for (const auto &hand : sortHands) {
      value <<= 4;
      value = value | (GET_RANK(hand) & 0xf);
    }
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
