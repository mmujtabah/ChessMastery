#include <iostream>
#include "Rook.h"

Rook::Rook(bool color, int x, int y) : ChessPiece(color, x, y)
{
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wr.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/wr.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/br.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/wr.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}
// bool King::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8])
//{
//	return false;
// }

ChessPiece::PieceState Rook::getPieceState()
{
	return State;
}