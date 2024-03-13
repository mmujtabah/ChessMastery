#include "Pawn.h"
#include <iostream>
Pawn::Pawn(int CurrentX, int CurrentY, int NextX, int NextY)
{
	this->CurrentX = CurrentX;
	this->CurrentY = CurrentY;
	this->NextX = NextX;
	this->NextY = NextY;
}
void Pawn::display()
{
	std::cout << "Current Coordinates: " << CurrentX << " " << CurrentY << std::endl;
	std::cout << "Next Coordinates: " << NextX << " " << NextY << std::endl;
}