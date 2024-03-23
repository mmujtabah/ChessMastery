#include <iostream>
#include "Rook.h"
Rook::Rook()
{
	color = 0;
	move = 0;
}

Rook::Rook(bool color)
{
	this->color = color;
	move = 0;
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wr.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/wr.png" << std::endl;
			return;
		}

	}
	else
	{
		if (!textures.loadFromFile("assets/images/br.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/wr.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true);// Set the smooth property for the texture
}
//bool King::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8])
//{
//	return false;
//}
