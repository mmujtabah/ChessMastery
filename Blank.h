#pragma once
#include "ChessPiece.h"
class Blank : public ChessPiece
{
private:
public:
    Blank();
    PieceState getPieceState() override;
};
