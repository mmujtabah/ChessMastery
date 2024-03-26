#include <iostream>
#include "Pawn.h"

Pawn::Pawn(bool color, int x, int y) : ChessPiece(color, x, y)
{
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