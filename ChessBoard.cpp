#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "Blank.h"

ChessBoard::ChessBoard() : event(), playButtonPressed(false)
{
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->CellSize = 0;
	this->endGame = false;
	this->window = nullptr;
	this->fonts = new sf::Font *[2];
	this->BackgroundTextures = new sf::Texture *[2];
	this->initFonts();
	this->initWindow();
	this->gameState = MENU;
	// Allocation for white
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn(0, 1, i);
	}
	board[0][7] = new Rook(0, 0, 7);
	board[0][0] = new Rook(0, 0, 0);
	board[0][6] = new Knight(0, 0, 6);
	board[0][1] = new Knight(0, 0, 1);
	board[0][5] = new Bishop(0, 0, 5);
	board[0][2] = new Bishop(0, 0, 2);
	board[0][4] = new Queen(0, 0, 4);
	board[0][3] = new King(0, 0, 3);

	// Allocation for black
	for (int i = 0; i < 8; i++)
	{
		board[6][i] = new Pawn(1, 6, i);
	}

	board[7][7] = new Rook(1, 7, 7);
	board[7][0] = new Rook(1, 7, 0);
	board[7][6] = new Knight(1, 7, 6);
	board[7][1] = new Knight(1, 7, 1);
	board[7][5] = new Bishop(1, 7, 5);
	board[7][2] = new Bishop(1, 7, 2);
	board[7][4] = new Queen(1, 7, 4);
	board[7][3] = new King(1, 7, 3);

	// For initializing blank space
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = new Blank(i, j);
		}
	}
}

void ChessBoard::initWindow()
{
	if (this->window == nullptr) // Check if window is not already created
	{
		this->window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Bejeweled Blitz", sf::Style::Close);
		this->screenWidth = window->getSize().x;
		this->screenHeight = window->getSize().y;
		this->window->setFramerateLimit(60);
		this->CellSize = std::min(screenWidth, screenHeight) / 10.0f;
		// Load Icon
		if (!this->Icon.loadFromFile("assets/images/icon.png"))
		{
			std::cout << "Failed to load icon file";
		}
		this->window->setIcon(this->Icon.getSize().x, this->Icon.getSize().y, this->Icon.getPixelsPtr());
		for (int i = 0; i < 2; ++i)
		{
			this->BackgroundTextures[i] = new sf::Texture;
			std::string imageFile = "assets/images/bg" + std::to_string(i) + ".jpg";
			if (!BackgroundTextures[i]->loadFromFile(imageFile))
			{
				std::cerr << "Failed to load font " << imageFile << "!" << std::endl;
				return;
			}
		}
		// Calculate the center of the window
		float centerX = this->screenWidth / 2.0f;
		float centerY = this->screenHeight / 2.0f;

		// Set button size and color
		float buttonWidth = 200;	// Width of the buttons
		float buttonHeight = 50;	// Height of the buttons
		float verticalSpacing = 20; // Spacing between buttons
		playButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
		exitButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
		playButton.setFillColor(sf::Color::Green); // Set color of the button
		exitButton.setFillColor(sf::Color::Red);   // Set color of the button

		// Calculate positions for play button
		playButton.setPosition(centerX - buttonWidth / 2, centerY - buttonHeight - verticalSpacing / 2);

		// Calculate positions for exit button
		exitButton.setPosition(centerX - buttonWidth / 2, centerY + verticalSpacing / 2);

		// Calculate positions for play button text
		playText.setFont(*fonts[0]); // Assuming you want to use the first font from the array
		playText.setCharacterSize(40);
		playText.setFillColor(sf::Color::White); // Set color of the text
		playText.setString("PLAY");
		// Center the text within the button
		playText.setPosition(playButton.getPosition() + sf::Vector2f((buttonWidth - playText.getLocalBounds().width) / 2, (buttonHeight - playText.getLocalBounds().height) / 2 - playText.getLocalBounds().top));

		// Calculate positions for exit button text
		exitText.setFont(*fonts[0]); // Assuming you want to use the first font from the array
		exitText.setCharacterSize(40);
		exitText.setFillColor(sf::Color::White); // Set color of the text
		exitText.setString("EXIT");
		// Center the text within the button
		exitText.setPosition(exitButton.getPosition() + sf::Vector2f((buttonWidth - exitText.getLocalBounds().width) / 2, (buttonHeight - exitText.getLocalBounds().height) / 2 - exitText.getLocalBounds().top));
	}
}

void ChessBoard::initFonts()
{
	// Load fonts into the fonts array
	for (int i = 0; i < 2; ++i)
	{
		this->fonts[i] = new sf::Font;
		std::string fontFilename = "assets/fonts/" + std::to_string(i) + ".ttf";
		if (!fonts[i]->loadFromFile(fontFilename))
		{
			std::cerr << "Failed to load font " << fontFilename << "!" << std::endl;
			// Handle failure (e.g., delete already loaded fonts and return)
			return;
		}
	}
}

bool ChessBoard::WindowIsOpen() const
{
	if (this->window != nullptr)
	{
		return this->window->isOpen();
	}
	else
	{
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
		case sf::Event::KeyPressed:
			handleKeyPress(this->event.key.code);
			break;
		}
	}
}

void ChessBoard::handleKeyPress(sf::Keyboard::Key key)
{
	if (gameState == MENU)
	{
		switch (key)
		{
		case sf::Keyboard::Up:
			if (highlighterPosition.y > 0)
				highlighterPosition.y--;
			break;
		case sf::Keyboard::Down:
			if (highlighterPosition.y < 1) // Assuming two menu items (play and exit)
				highlighterPosition.y++;
			break;
		case sf::Keyboard::Return:			// Enter key
			if (highlighterPosition.y == 0) // Play selected
				gameState = PLAYING;
			else // Exit selected
				window->close();
			break;
		}
	}
	else
	{

		switch (key)
		{
		case sf::Keyboard::Up:
			if (highlighterPosition.y > 0)
				highlighterPosition.y--;
			break;
		case sf::Keyboard::Down:
			if (highlighterPosition.y < 7)
				highlighterPosition.y++;
			break;
		case sf::Keyboard::Left:
			if (highlighterPosition.x > 0)
				highlighterPosition.x--;
			break;
		case sf::Keyboard::Right:
			if (highlighterPosition.x < 7)
				highlighterPosition.x++;
			break;
		}
	}
}

void ChessBoard::drawBoard()
{
	// Clear the window
	this->window->clear();
	sf::Sprite BackgroundSprite;
	sf::RectangleShape highlighter; // Declare highlighter here

	// Declare xPos and yPos here
	float xPos, yPos;

	// Check the game state
	switch (gameState)
	{
	case MENU:
		// Draw menu buttons
		BackgroundSprite.setTexture(*BackgroundTextures[0]);
		BackgroundSprite.setScale(static_cast<float>(screenWidth) / BackgroundSprite.getLocalBounds().width, static_cast<float>(screenHeight) / BackgroundSprite.getLocalBounds().height);
		this->window->draw(BackgroundSprite);
		this->window->draw(playButton);
		this->window->draw(exitButton);
		this->window->draw(playText);
		this->window->draw(exitText);

		// Draw the highlighter
		xPos = playButton.getPosition().x;
		yPos = playButton.getPosition().y + highlighterPosition.y * (playButton.getSize().y + 20);
		highlighter.setSize(sf::Vector2f(playButton.getSize().x, playButton.getSize().y)); // Initialize highlighter size
		highlighter.setPosition(xPos, yPos);
		highlighter.setFillColor(sf::Color(255, 255, 0, 100)); // Semi-transparent yellow
		this->window->draw(highlighter);
		break;
	case PLAYING:
		// Draw the chessboard
		BackgroundSprite.setTexture(*BackgroundTextures[1]);
		BackgroundSprite.setScale(static_cast<float>(screenWidth) / BackgroundSprite.getLocalBounds().width, static_cast<float>(screenHeight) / BackgroundSprite.getLocalBounds().height);
		this->window->draw(BackgroundSprite);
		float leftMargin = (this->window->getSize().x - (10 * this->CellSize)) / 10;
		float topMargin = (window->getSize().y - (8 * this->CellSize)) / 5;

		// Draw cells
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// Draw board cell
				if ((i + j) % 2 == 0)
				{
					boardShape.setFillColor(sf::Color(239, 237, 209)); // Milk White
				}
				else
				{
					boardShape.setFillColor(sf::Color(201, 128, 60)); // Copper
				}
				float PositionX = leftMargin + j * this->CellSize, PositionY = topMargin + i * this->CellSize;
				boardShape.setSize(sf::Vector2f(this->CellSize, this->CellSize));
				boardShape.setPosition(PositionX, PositionY);
				this->window->draw(boardShape);
				// Draw piece sprite if there's a piece at this position
				if (board[i][j]->getPieceState() == ChessPiece::PIECE)
				{
					sf::Sprite sprite;
					sprite.setTexture(board[i][j]->textures); // Set the texture
					float scale = this->CellSize / static_cast<float>(board[i][j]->textures.getSize().x);
					sprite.setScale(scale, scale);
					float OffsetX = (this->CellSize - sprite.getGlobalBounds().width) / 2.0f;
					float OffsetY = (this->CellSize - sprite.getGlobalBounds().height) / 2.0f;
					sprite.setPosition(PositionX + OffsetX, PositionY + OffsetY);
					window->draw(sprite);
				}
			}
		}

		// Draw the highlighter
		xPos = leftMargin + highlighterPosition.x * this->CellSize;
		yPos = topMargin + highlighterPosition.y * this->CellSize;
		highlighter.setSize(sf::Vector2f(this->CellSize, this->CellSize)); // Initialize highlighter size
		highlighter.setPosition(xPos, yPos);
		highlighter.setFillColor(sf::Color(255, 255, 0, 100)); // Semi-transparent yellow
		this->window->draw(highlighter);
		break;
	}

	// Display the window contents
	this->window->display();
}

ChessBoard::GameState ChessBoard::getGameState()
{
	return gameState;
}

void ChessBoard::renderWindow()
{
	this->window->display();
}

ChessBoard::~ChessBoard()
{
	// Delete fonts
	if (fonts != nullptr)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (fonts[i] != nullptr)
			{
				delete fonts[i];
			}
		}
		delete[] fonts;
	}

	// Delete window
	if (window != nullptr)
	{
		delete window;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete board[i][j];
		}
	}
	// Set pointers to null
	window = nullptr;
	fonts = nullptr;
}