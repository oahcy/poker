#include "texas.h"
#include "6_calcWinRate.h"
#include "5_calcTexasHand.h"
#include <random>

void GenAllCards(std::vector<int> &allCards) {
  for (int i = 0; i < SUIT_COUNTS; i++) {
    for (int j = 0; j < RANK_COUNTS; j++) {
      int rank = ((i + 1) << 8) + j + 2;
      allCards.push_back(rank);
    }
  }
}

std::vector<int> GetTwoRandNumber(int cards) {
  std::vector<int> retRand;
  static std::default_random_engine e(time(0));
  std::uniform_int_distribution<unsigned> u(0, cards - 1);
  std::uniform_int_distribution<unsigned> u2(0, cards - 2);
  int rand1 = u(e);
  int rand2 = u2(e);
  if (rand2 >= rand1) {
    rand2 ++;
  }
  assert(rand1 != rand2);
  assert(rand1 < cards);
  assert(rand2 < cards);
  retRand.push_back(rand1);
  retRand.push_back(rand2);
  return retRand;
}

int GetWinRateAtRiver(const std::vector<int>& self, const std::vector<int>& board) {
  std::vector<int> allHands = self;
  allHands.insert(allHands.end(), board.begin(), board.end());
  std::vector<int> maxHands;
  uint32_t maxValue = 0;
  GetTexasMaxHands(allHands, maxHands, maxValue);

  std::vector<int> leftCards;
  GenAllCards(leftCards);
  for (const auto &card : allHands) {
    auto removeIter = std::remove(leftCards.begin(), leftCards.end(), card);
    assert(removeIter != leftCards.end());
    leftCards.erase(removeIter);
  }
  int winCounts = 0;
  for (int i = 0; i < RANDOMTIMES; i++) {
    auto randNums = GetTwoRandNumber(leftCards.size());
    auto randPlayerHands = board;
    randPlayerHands.push_back(leftCards[randNums[0]]),
    randPlayerHands.push_back(leftCards[randNums[1]]);
    std::vector<int> randMaxHands;
    uint32_t randMaxValue = 0;
    GetTexasMaxHands(randPlayerHands, randMaxHands, randMaxValue);
    if (randMaxValue < maxValue) {
      winCounts++;
    }
  }
  auto percent = winCounts / (RANDOMTIMES / 100);
  return percent;
}