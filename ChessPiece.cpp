#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessPiece.h"

ChessPiece::ChessPiece(bool color, int x, int y, int value)
{
	this->move = 0;
	this->color = color;
	this->x = x; // Initialize x and y here if needed
	this->y = y;
	this->value = value;
	State = PIECE;
}
bool ChessPiece::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece *board[8][8])
{
	if (board[xto][yto]->getPieceState() == BLANK || (((!(board[yto][xto]->color)) && board[yfrom][xfrom]->color) || (board[yto][xto]->color && (!(board[yfrom][xfrom]->color)))))
	{
		move = true;
		return true;
	}
	else
	{
		return false;
	}
}

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

int ChessPiece::getValue()
{
	return this->value;
}

ChessPiece::~ChessPiece()
{
}