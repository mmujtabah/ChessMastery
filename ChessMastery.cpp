#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessBoard.h"


int main()
{
    ChessBoard* obj = new ChessBoard(); // Allocate ChessBoard object on the heap
    obj->initWindow();

    while (obj->WindowIsOpen())
    {
        obj->pollEvents();
        obj->renderWindow();
        obj->drawBoard();
    } 
    delete obj; // Deallocate ChessBoard object from the heap
    return 0;
}
