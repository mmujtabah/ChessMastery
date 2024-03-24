#pragma once
#include "ChessPiece.h"
class Pawn : public ChessPiece
{
private:
public:
	Pawn();
	Pawn(bool color);
	PieceState getPieceState() override;
};
