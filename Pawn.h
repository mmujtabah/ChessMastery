#pragma once
#include "ChessPiece.h"
class Pawn : public ChessPiece
{
private:
public:
	Pawn(bool color, int x, int y);
	PieceState getPieceState() override;
	bool isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece *board[8][8]) override;
};
