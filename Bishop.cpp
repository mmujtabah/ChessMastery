#include <iostream>
#include "Bishop.h"

Bishop::Bishop(bool color, int x, int y) : ChessPiece(color, x, y, 0)
{
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wb.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/wb.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/bb.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bb.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}

ChessPiece::PieceState Bishop::getPieceState()
{
	// Implement the function here
	return State;
}