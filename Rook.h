#pragma once
#include "ChessPiece.h"
class Rook : public ChessPiece
{
private:
public:
	Rook(bool color, int x, int y);
	PieceState getPieceState() override;
};
