#include "Blank.h"

Blank::Blank(int x, int y) : ChessPiece(false, 0, 0, 0)
{
    State = BLANK;
}
int Blank::getX()
{
    return this->x;
}
int Blank::getY()
{
    return this->y;
}
ChessPiece::PieceState Blank::getPieceState()
{
    return State;
}