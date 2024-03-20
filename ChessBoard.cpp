#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessBoard.h"

ChessBoard::ChessBoard() : event()
{
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->CellSize = 0;
	this->endGame = false;
	this->boardData = nullptr;
	this->window = nullptr;
	
	this->boardData = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		this->boardData[i] = new int[8];
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->boardData[i][j] = -1;
		}
	}
	// Placing White and Black Pieces
	for (int i = 0; i < 6; i++)
	{
		this->boardData[0][i] = 6 + i;
		this->boardData[7][i] = i;
	}
	// Placing Pieces After King
	for (int i = 5, j = 2; i < 8 && j >= 0; i++, j--)
	{
		this->boardData[0][i] = 6 + j;
		this->boardData[7][i] = j;
	}
	// Placing Pawns
	for (int i = 0; i < 8; i++)
	{
		this->boardData[1][i] = 11;
		this->boardData[6][i] = 5;
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

void ChessBoard::initWindow()
{
	this->desktopMode = sf::VideoMode::getDesktopMode();
	this->screenWidth = desktopMode.width;
	this->screenHeight = desktopMode.height;
	this->window = new sf::RenderWindow(this->desktopMode, "Chess Mastery", sf::Style::Default);
	this->window->setFramerateLimit(60);
	this->CellSize = std::min(screenWidth, screenHeight) / 10.0f;
	if (!this->Icon.loadFromFile("assets/images/icon.png"))
	{
		std::cout << "Failed to load icon file";
	}
	this->window->setIcon(this->Icon.getSize().x, this->Icon.getSize().y, this->Icon.getPixelsPtr());
}

bool ChessBoard::WindowIsOpen() const
{
	if (this->window != nullptr) {
		return this->window->isOpen();
	}
	else {
		// Handle the case where window is not initialized
		std::cout << "Window not initialized";
		return false;
	}
}

void ChessBoard::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void ChessBoard::drawBoard()
{
	// Calculate left and top margins
	float leftMargin = (this->window->getSize().x - (10 * this->CellSize)) / 5;
	float topMargin = (window->getSize().y - (8 * this->CellSize)) / 1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// Draw board cell
			if ((i + j) % 2 == 0)
			{
				board[i][j].setFillColor(sf::Color(239, 237, 209)); // Milk White
			}
			else
			{
				board[i][j].setFillColor(sf::Color(120, 150, 86)); // Green
			}
			float PositionX = leftMargin + j * this->CellSize, PositionY = topMargin + i * this->CellSize;
			board[i][j].setSize(sf::Vector2f(this->CellSize, this->CellSize));
			board[i][j].setPosition(PositionX, PositionY);
			this->window->draw(board[i][j]);

			// Draw piece sprite if there's a piece at this position
			if (boardData[i][j] != -1)
			{
				sf::Sprite sprite;
				sprite.setTexture(textures[boardData[i][j]]); // Set the texture
				float scale = this->CellSize / static_cast<float>(textures[boardData[i][j]].getSize().x);
				sprite.setScale(scale, scale);
				float OffsetX = (this->CellSize - sprite.getGlobalBounds().width) / 2.0f;
				float OffsetY = (this->CellSize - sprite.getGlobalBounds().height) / 2.0f;
				sprite.setPosition(PositionX + OffsetX, PositionY + OffsetY);
				window->draw(sprite);
			}
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

void ChessBoard::renderWindow()
{
	this->window->display();
}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < 8; i++)
	{
		delete[] boardData[i];
	}
	delete[] boardData;
	delete this->window;
	boardData = nullptr;
	window = nullptr;
}