#pragma once
#include "ChessPiece.h"
class Pawn : public ChessPiece
{
private:
public:
	Pawn(bool color, int x, int y);
	PieceState getPieceState() override;
};
