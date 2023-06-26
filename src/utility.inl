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

#ifdef _WIN32
#include <conio.h>
#else
#ifdef __linux__
#include <termio.h>
#include <cstdio>
#elif __APPLE__
#include <termios.h>
#endif
inline char getch(void)
{
    struct termios tmtemp, tm;
    char c;
    int fd = 0;
    if (tcgetattr(fd, &tm) != 0)
    {
        //obtain current terminal properties setting, save it in tm
        return -1;
    }
    tmtemp = tm;
    cfmakeraw(&tmtemp); //initialize tmtemp to the properties setting of orginal terminal mode
    if (tcsetattr(fd, TCSANOW, &tmtemp) != 0)
    {
        /*set terminal to setting of original mode*/
        return -1;
    }
    c = getchar();
    if (tcsetattr(fd, TCSANOW, &tm) != 0)
    {
        //set terminal to previous properties after receiving the character
        return 0;
    }
    return c;
}
#endif

inline void cls(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif