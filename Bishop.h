#pragma once
#include "ChessPiece.h"
class Bishop : public ChessPiece
{
private:
public:
	Bishop(bool color, int x, int y);
	PieceState getPieceState() override;
};
