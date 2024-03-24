#pragma once
#include "ChessPiece.h"
class Queen : public ChessPiece
{
private:
public:
	Queen();
	Queen(bool color);
	PieceState getPieceState() override;
};
