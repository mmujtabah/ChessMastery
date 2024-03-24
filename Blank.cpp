#include "Blank.h"

Blank::Blank()
{
    State = BLANK;
}

ChessPiece::PieceState Blank::getPieceState()
{
    return State;
}