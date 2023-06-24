#ifndef _SUDOKU_UTILITY_INL_
#define _SUDOKU_UTILITY_INL_

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>

/*
@function return number between [begin, end]
*/
inline unsigned int random(int begin, int end)
{
    assert(end >= begin && begin >= 0);
    srand(time(NULL));
    return (unsigned int)rand() % (end - begin + 1) + begin;
}

inline void message(const char *msg = "", bool lf = true)
{
    std::cout << msg;
    if (lf)
        std::cout << std::endl;
}

inline void cls(void)
{
    system("clear");
}

#endif