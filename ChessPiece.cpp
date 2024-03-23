#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessPiece.h"

ChessPiece::ChessPiece()
{
	this->move = 0;
	this->color = 0;
}
//bool ChessPiece::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8])
//{
//
//}
ChessPiece::~ChessPiece()
{

}