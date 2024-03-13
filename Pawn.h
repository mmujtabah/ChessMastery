#pragma once

class Pawn
{
private: int CurrentX, CurrentY, NextX, NextY;
public:
	Pawn(int CurrentX = 0, int CurrentY = 0, int NextX = 1, int NextY = 0);
	void display();
};