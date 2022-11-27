#include <iostream>
#include <vector>
#include "texas.h"
#include "utils.h"
#include "calcPoker.h"

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

int main()
{
    std::cout << "test 1" << std::endl;
    std::cout << helloWorld() << std::endl;

    std::cout << "test 2" << std::endl;
    for (int i = 0; i < s_test2.size(); i++)
    {
        auto const input = s_test2[i];
        printVector(input);
        std::cout << " sort ->  " << sort(input) << std::endl;
    }

    std::cout << "test 3" << std::endl;
    for (int i = 0; i < s_test3.size(); i++)
    {
        auto const input = s_test3[i];
        printPoker(input);
        PokerHand pokerHand;
        if (ConvertHand(pokerHand, input) == 0) {
            HandType t = GetHandType(pokerHand);
            std::cout << " type ->  " << t << ":" << ConvertTypeToString(t) << std::endl;
        }
    }

    return 0;
}