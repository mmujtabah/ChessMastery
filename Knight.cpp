#include <iostream>
#include "Knight.h"

Knight::Knight()
{
	color = 0;
	move = 0;
}

Knight::Knight(bool color)
{
	this->color = color;
	move = 0;
	this->color = color;
	move = 0;
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wn.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/wn.png" << std::endl;
			return;
		}

	}
	else
	{
		if (!textures.loadFromFile("assets/images/bn.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/bn.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true);// Set the smooth property for the texture
}