#pragma once
#include "ChessPiece.h"
class Rook : public ChessPiece
{
private:
public:
	Rook();
	Rook(bool color);
	PieceState getPieceState() override;
};
