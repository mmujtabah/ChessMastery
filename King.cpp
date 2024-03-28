#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "King.h"

King::King(bool color, int x, int y) : ChessPiece(color, x, y, 6)
{

	if (color)
	{
		if (!textures.loadFromFile("assets/images/wk.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/wk.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/bk.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bk.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}
// bool King::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8])
//{
//	return false;
// }

ChessPiece::PieceState King::getPieceState()
{
	return State;
}