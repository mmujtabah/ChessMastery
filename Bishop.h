#pragma once
#include "ChessPiece.h"
class Bishop : public ChessPiece
{
private:
public:
	Bishop();
	Bishop(bool color);
	PieceState getPieceState() override;
};

