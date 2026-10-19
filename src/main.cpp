#include "Game.h"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}