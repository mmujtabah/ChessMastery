#include <iostream>
#include "Bishop.h"

Bishop::Bishop()
{
	color = 0;
	move = 0;
}

Bishop::Bishop(bool color)
{
	this->color = color;
	move = 0;
	this->color = color;
	move = 0;
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wb.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/wb.png" << std::endl;
			return;
		}

	}
	else
	{
		if (!textures.loadFromFile("assets/images/bb.png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/bb.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true);// Set the smooth property for the texture
}