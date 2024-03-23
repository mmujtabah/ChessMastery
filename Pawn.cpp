#include <iostream>
#include "Pawn.h"

Pawn::Pawn()
{
	color = 0;
	move = 0;
}

Pawn::Pawn(bool color)
{
	this->color = color;
	move = 0;
	this->color = color;
	move = 0;
	if (color)
	{
		if (!textures.loadFromFile("assets/images/bp.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/bp.png" << std::endl;
			return;
		}

	}
	else
	{
		if (!textures.loadFromFile("assets/images/bp.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/bp.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true);// Set the smooth property for the texture

}