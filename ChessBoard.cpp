#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	boardData = nullptr;
	boardData = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		boardData[i] = new int[8];
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boardData[i][j] = -1;
		}
	}
	// Placing White and Black Pieces
	for (int i = 0; i < 6; i++)
	{
		boardData[0][i] = 6 + i;
		boardData[7][i] = i;
	}
	// Placing Pieces After King
	for (int i = 5, j = 2; i < 8 && j >= 0; i++, j--)
	{
		boardData[0][i] = 6 + j;
		boardData[7][i] = j;
	}
	// Placing Pawns
	for (int i = 0; i < 8; i++)
	{
		boardData[1][i] = 11;
		boardData[6][i] = 5;
	}
	// Load Image Textures
	for (int i = 0; i < 12; i++)
	{
		if (!textures[i].loadFromFile("assets/images/" + std::to_string(i) + ".png"))
		{
			std::cout << "Failed to load texture: " << "assets/images/" + std::to_string(i) + ".png" << std::endl;
			return;
		}
		textures[i].setSmooth(true);// Set the smooth property for the texture
	}
}

void ChessBoard::drawBoard(sf::RenderWindow& window, sf::RectangleShape board[][8], float cellSize, int screenWidth, int screenHeight)
{
	// Calculate left and top margins
	float leftMargin = (window.getSize().x - (10 * cellSize)) / 5;
	float topMargin = (window.getSize().y - (8 * cellSize)) / 1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sf::Sprite sprite;
			board[i][j].setSize(sf::Vector2f(cellSize, cellSize));
			int index = boardData[i][j];
			sprite.setTexture(textures[boardData[i][j]]); // Set the texture
			// Adjust position calculation to include margins
			float PositionX = leftMargin + j * cellSize, PositionY = topMargin + i * cellSize;
			board[i][j].setPosition(PositionX, PositionY);
			float scale = cellSize / static_cast<float>(textures[boardData[i][j]].getSize().x);
			sprite.setScale(scale, scale);
			float OffsetX = (cellSize - sprite.getGlobalBounds().width) / 2.0f;
			float OffsetY = (cellSize - sprite.getGlobalBounds().height) / 2.0f;
			sprite.setPosition(PositionX + OffsetX, PositionY + OffsetY);
			if ((i + j) % 2 == 0)
			{
				board[i][j].setFillColor(sf::Color(239, 237, 209)); // Milk White
			}
			else
			{
				board[i][j].setFillColor(sf::Color(120, 150, 86)); // Green
			}
			window.draw(board[i][j]);
			window.draw(sprite);
		}
	}
}



void ChessBoard::drawMatrix()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << boardData[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < 8; i++)
	{
		delete[] boardData[i];
	}
	delete[] boardData;
	boardData = nullptr;
}