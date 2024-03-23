#pragma once
#include "ChessPiece.h"
class King : public ChessPiece
{
public:
	King();
	King(bool color);
	//bool isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8]) override;
};

