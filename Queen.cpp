#include <iostream>
#include "Queen.h"
Queen::Queen()
{
	color = 0;
	move = 0;
}
Queen::Queen(bool color)
{
	this->color = color;
	move = 0;
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wq.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/wq.png" << std::endl;
			return;
		}

	}
	else
	{
		if (!textures.loadFromFile("assets/images/bq.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/bq.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true);// Set the smooth property for the texture
}