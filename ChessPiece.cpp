#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessPiece.h"

ChessPiece::ChessPiece(bool color, int x, int y)
{
	this->move = 0;
	this->color = color;
	this->x = x; // Initialize x and y here if needed
	this->y = y;
	State = PIECE;
}
// bool ChessPiece::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8])
//{
//
// }

void ChessPiece::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int ChessPiece::getX()
{
	return this->x;
}

int ChessPiece::getY()
{
	return this->y;
}

ChessPiece::~ChessPiece()
{
}