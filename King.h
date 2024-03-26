#pragma once
#include "ChessPiece.h"
class King : public ChessPiece
{
public:
	King(bool color, int x, int y);
	// bool isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8]) override;
	PieceState getPieceState() override;
};
