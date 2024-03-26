#pragma once
#include "ChessPiece.h"
class Blank : public ChessPiece
{
private:
public:
    Blank(int x, int y);
    int getX();
    int getY();
    PieceState getPieceState() override;
};
