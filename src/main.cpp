#include <iostream>
#include <vector>
#include "texas.h"
#include "utils.h"
#include "3_calcPoker.h"

std::vector<std::vector<int> > s_test2{
    {45, 62, 83, 25, 83, 23, 83, 23, 56, 2, 72, 634, 64},
    {34, 6, 235, 734, 7, 8, 3, 34, 5, 78, 34},
    {9, 8, 7, 6, 5, 4, 3, 2, 1},
    {}
};

std::vector<std::vector<int> > s_test3{
    {0x102,0x103,0x105,0x104,0x30e}, //a2345
    {0x209,0x104,0x10b,0x10c,0x10d}, //no pair
    {0x109,0x40a,0x20b,0x30b,0x106}, //pair
    {0x106,0x40a,0x205,0x305,0x106}, //two pair
    {0x109,0x409,0x209,0x305,0x106}, //trips
    {0x104,0x406,0x205,0x307,0x108}, //staight
    {0x309,0x30a,0x30b,0x305,0x306}, //flush
    {0x209,0x408,0x209,0x308,0x109}, //full house
    {0x206,0x407,0x406,0x306,0x106}, //quads
    {0x209,0x208,0x207,0x20a,0x206}, //straightFlush
    {0x10a,0x10e,0x10c,0x10b,0x10d}, //royalStraightFlush
    {0x102,0x105,0x103,0x104,0x10e},
    {}
};

std::vector<std::vector<int> > s_test4{
    //on joker
    {0x102,0x103,0x50f,0x104,0x30e}, //a2345
    {0x209,0x104,0x10b,0x50f,0x10d}, //no pair
    {0x109,0x50f,0x20b,0x30b,0x106}, //pair
    {0x106,0x610,0x205,0x305,0x106}, //two pair
    {0x109,0x409,0x209,0x610,0x106}, //trips
    {0x104,0x406,0x205,0x307,0x50f}, //staight
    {0x50f,0x30a,0x30b,0x305,0x306}, //flush
    {0x209,0x408,0x50f,0x308,0x109}, //full house
    {0x206,0x407,0x50f,0x306,0x106}, //quads
    {0x50f,0x208,0x207,0x20a,0x206}, //straightFlush
    {0x102,0x103,0x50f,0x104,0x10e}, //a2345
    {0x10a,0x10e,0x50f,0x10b,0x10d}, //royalStraightFlush

    //two joker
        //on joker
    {0x102,0x103,0x50f,0x104,0x610}, //a2345
    {0x109,0x50f,0x209,0x610,0x106}, //trips
    {0x104,0x406,0x610,0x307,0x50f}, //staight
    {0x50f,0x30a,0x610,0x305,0x306}, //flush
    {0x209,0x408,0x50f,0x308,0x610}, //quads
    {0x610,0x407,0x50f,0x306,0x106}, //quads
    {0x50f,0x208,0x207,0x610,0x206}, //straightFlush
    {0x10a,0x10e,0x50f,0x10b,0x610}, //royalStraightFlush
    {}
};

std::vector<std::vector<int> > s_test5_self{
    {0x104,0x30e},
    {0x305,0x10d},
};

std::vector<std::vector<int> > s_test5_board{
    {0x307,0x205, 0x109, 0x108, 0x203},
    {0x202,0x105, 0x10e, 0x403, 0x405},
};

int main()
{
    std::cout << ">>>test 1, hello world." << std::endl;
    std::cout << helloWorld() << std::endl;

    std::cout << ">>>test 2, sort." << std::endl;
    for (int i = 0; i < s_test2.size(); i++)
    {
        auto const input = s_test2[i];
        printVector(input);
        std::cout << " sort ->  " << sort(input) << std::endl;
    }

    std::cout << ">>>test 3, calculate hand type." << std::endl;
    for (int i = 0; i < s_test3.size(); i++) {
      auto const input = s_test3[i];
      printPoker(input);
      HandType t = GetHandType(input);
      std::cout << " type ->  " << t << ":" << ConvertTypeToString(t)
                << std::endl;
    }

    std::cout << ">>>test 4, calculate joker hand type." << std::endl;
    for (int i = 0; i < s_test4.size(); i++) {
      auto const input = s_test4[i];
      printPoker(input);
      HandType t = GetJokerHandType(input);
      std::cout << " type ->  " << t << ":" << ConvertTypeToString(t)
                << std::endl;
    }

    std::cout << ">>>test 5, calculate hand type in Texas." << std::endl;
    for (int i = 0; i < s_test5_self.size(); i++) {
      for (int j = 0; j < s_test5_board.size(); j++) {
        auto selfCards = s_test5_self[i];
        auto boardCards = s_test5_board[j];
        printPoker(selfCards);
        std::cout << ", board: ";
        printPoker(boardCards);
        HandType t = GetTexasHandType(selfCards, boardCards);
        std::cout << " type ->  " << t << ":" << ConvertTypeToString(t)
                  << std::endl;
      }
    }

    std::cout << ">>>test 6, calculate win rate at river." << std::endl;
    for (int i = 0; i < s_test5_self.size(); i++) {
      for (int j = 0; j < s_test5_board.size(); j++) {
        auto selfCards = s_test5_self[i];
        auto boardCards = s_test5_board[j];
        printPoker(selfCards);
        std::cout << ", board: ";
        printPoker(boardCards);
        int rate = GetWinRateAtRiver(selfCards, boardCards);
        std::cout << " rate ->  " << rate << "%" << std::endl;
      }
    }
    return 0;
}