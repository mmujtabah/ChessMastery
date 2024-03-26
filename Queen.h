#pragma once
#include "ChessPiece.h"
class Queen : public ChessPiece
{
private:
public:
	Queen(bool color, int x, int y);
	PieceState getPieceState() override;
};
