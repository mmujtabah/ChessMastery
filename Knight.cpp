#include <iostream>
#include "Knight.h"

Knight::Knight(bool color, int x, int y) : ChessPiece(color, x, y)
{
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wn.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/wn.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/bn.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bn.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}

ChessPiece::PieceState Knight::getPieceState()
{
	// Implement the function here
	return State;
}