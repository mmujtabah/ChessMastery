#include <iostream>
#include "Pawn.h"

Pawn::Pawn(bool color, int x, int y) : ChessPiece(color, x, y, 1)
{
	if (color)
	{
		if (!textures.loadFromFile("assets/images/wp.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bp.png" << std::endl;
			return;
		}
	}
	else
	{
		if (!textures.loadFromFile("assets/images/bp.png"))
		{
			std::cout << "Failed to load texture: "
					  << "assets/images/bp.png" << std::endl;
			return;
		}
	}
	textures.setSmooth(true); // Set the smooth property for the texture
}

ChessPiece::PieceState Pawn::getPieceState()
{
	return State;
}

bool Pawn::isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece *board[8][8])
{
	// Check if the destination is within the board boundaries
	if (xto < 0 || xto >= 8 || yto < 0 || yto >= 8)
	{
		return false;
	}

	// White pawn moves
	if (color)
	{
		// Moving forward one square
		if (xto == xfrom - 1 && yto == yfrom && board[xto][yto]->getPieceState() == ChessPiece::BLANK)
		{
			return true;
		}
		// Moving forward two squares on the first move
		if (xto == xfrom - 2 && yto == yfrom && xfrom == 6 && board[xto][yto]->getPieceState() == ChessPiece::BLANK && board[xto + 1][yto]->getPieceState() == ChessPiece::BLANK)
		{
			return true;
		}
		// Capturing diagonally
		if (xto == xfrom - 1 && (yto == yfrom + 1 || yto == yfrom - 1) && board[xto][yto]->getPieceState() != ChessPiece::BLANK && board[xto][yto]->getValue() != 6)
		{
			return true;
		}
	}
	// Black pawn moves
	else
	{
		// Moving forward one square
		if (xto == xfrom + 1 && yto == yfrom && board[xto][yto]->getPieceState() == ChessPiece::BLANK)
		{
			return true;
		}
		// Moving forward two squares on the first move
		if (xto == xfrom + 2 && yto == yfrom && xfrom == 1 && board[xto][yto]->getPieceState() == ChessPiece::BLANK && board[xto - 1][yto]->getPieceState() == ChessPiece::BLANK)
		{
			return true;
		}
		// Capturing diagonally
		if (xto == xfrom + 1 && (yto == yfrom + 1 || yto == yfrom - 1) && board[xto][yto]->getPieceState() != ChessPiece::BLANK && board[xto][yto]->getValue() != 6)
		{
			return true;
		}
	}
	return false;
}