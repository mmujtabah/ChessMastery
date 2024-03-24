#include <iostream>
#include "Pawn.h"

Pawn::Pawn()
{
	color = 0;
	move = 0;
	State = PIECE;
}

Pawn::Pawn(bool color)
{
	this->color = color;
	move = 0;
	State = PIECE;
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wp.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bp.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/bp.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bp.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}

ChessPiece::PieceState Pawn::getPieceState()
{
	return State;
}