#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessWindow.h"

int main()
{
    ChessWindow *game = new ChessWindow();
    game->initWindow();

    while (game->WindowIsOpen())
    {
        game->windowUpdate();
    }

    delete game;
    return 0;
}
