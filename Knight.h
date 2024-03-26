#pragma once
#include "ChessPiece.h"
class Knight : public ChessPiece
{
private:
public:
	Knight(bool color, int x, int y);
	PieceState getPieceState() override;
};
