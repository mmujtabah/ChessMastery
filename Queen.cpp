#include <iostream>
#include "Queen.h"

Queen::Queen(bool color, int x, int y) : ChessPiece(color, x, y)
{
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wq.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/wq.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/bq.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bq.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}

ChessPiece::PieceState Queen::getPieceState()
{
	return State;
}