#include <iostream>
#include <sstream>
#include <string>
#include "common.h"
#include "utility.inl"

/*
@function return number of grids to be erased
*/
int inputDifficulty()
{
    cls();

    std::string cmd;
    int need_erase_grids = 0;
    while (true)
    {
        std::cout << "Set Mode: 1 Easy 2 Normal 3 HARD" << std::endl;
        std::cin >> cmd;

        try
        {
            Difficulty difficulty = static_cast<Difficulty>(std::stoi(cmd));
            switch (difficulty)
            {
            case Difficulty::EASY:
                need_erase_grids = 20;
                break;
            case Difficulty::NORMAL:
                need_erase_grids = 35;
                break;
            case Difficulty::HARD:
                need_erase_grids = 50;
                break;
            }
        }
        catch (...)
        {
            need_erase_grids = 0;
        }

        if (need_erase_grids > 0)
            break;

        std::cout << "Input Error! " << std::endl;
    }

    return need_erase_grids;
}

KeyMode inputKeyMode()
{
    std::string mode;
    do
    {
        message("Set Input Mode: 1 Normal 2 VIM");

        std::cin >> mode;

        try
        {
            KeyMode kmd = static_cast<KeyMode>(std::stoi(mode));
            return kmd;
        }
        catch (...)
        {
        }

        message("Input Error! ");

    } while (true);
}