#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessWindow.h"
#include "ChessPiece.h"

int main()
{
    ChessBoard board;
    ChessWindow *game = new ChessWindow(board);
    game->initWindow();

    while (game->WindowIsOpen())
    {
        game->windowUpdate();
    }

    delete game;
    return 0;
}
