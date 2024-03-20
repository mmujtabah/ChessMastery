#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessBoard.h"

ChessBoard::ChessBoard() : event(), playButtonPressed(false)
{
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->CellSize = 0;
	this->endGame = false;
	this->boardData = nullptr;
	this->window = nullptr;
	this->fonts = new sf::Font *[2];
	this->initFonts();
	this->initWindow();
	this->gameState = MENU;
	// Initialize play button
	playButton.setSize(sf::Vector2f(200, 50)); // Set size of the button
	playButton.setPosition(100, 200); // Set position of the button
	playButton.setFillColor(sf::Color::Green); // Set color of the button

	// Initialize exit button
	exitButton.setSize(sf::Vector2f(200, 50)); // Set size of the button
	exitButton.setPosition(100, 300); // Set position of the button
	exitButton.setFillColor(sf::Color::Red); // Set color of the button
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
}

void ChessBoard::initWindow()
{
	this->desktopMode = sf::VideoMode::getDesktopMode();
	this->screenWidth = desktopMode.width;
	this->screenHeight = desktopMode.height;
	this->window = new sf::RenderWindow(this->desktopMode, "Chess Mastery", sf::Style::Default);
	this->window->setFramerateLimit(60);
	this->CellSize = std::min(screenWidth, screenHeight) / 10.0f;
	// Load Icon
	if (!this->Icon.loadFromFile("assets/images/icon.png"))
	{
		std::cout << "Failed to load icon file";
	}
	this->window->setIcon(this->Icon.getSize().x, this->Icon.getSize().y, this->Icon.getPixelsPtr());
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
	playText.setFont(*fonts[0]); // Assuming you want to use the first font from the array
	playText.setCharacterSize(40);
	playText.setFillColor(sf::Color::Red);
	playText.setString("Play");
	playText.setPosition(400.0f, 420.0f);
	playText.setOutlineThickness(2.0f);
	exitText.setFont(*fonts[0]); // Assuming you want to use the first font from the array
	exitText.setCharacterSize(40);
	exitText.setFillColor(sf::Color::Red);
	exitText.setString("Exit");
	exitText.setPosition(400.0f, 420.0f);
	exitText.setOutlineThickness(2.0f);
}

void ChessBoard::initFonts()
{
	// Load fonts into the fonts array
	for (int i = 0; i < 2; ++i) {
		this->fonts[i] = new sf::Font;
		std::string fontFilename = "assets/fonts/" + std::to_string(i) + ".ttf";
		if (!fonts[i]->loadFromFile(fontFilename)) {
			std::cerr << "Failed to load font " << fontFilename << "!" << std::endl;
			// Handle failure (e.g., delete already loaded fonts and return)
			return;
		}
	}
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

void ChessBoard::handleMouseClick(const sf::Vector2i& mousePosition)
{
	// Check if the click is within the bounds of the "Play" button
	if (gameState == MENU && playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
		// Start the game
		gameState = PLAYING;

	}
	// Check if the click is within the bounds of the "Exit" button
	else if (gameState == MENU && exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
		// Close the window
		window->close();
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
		case sf::Event::MouseButtonPressed:
			if (this->event.mouseButton.button == sf::Mouse::Left) {
				handleMouseClick(sf::Mouse::getPosition(*window));
			}
			break;
		}
	}
}

void ChessBoard::drawBoard()
{
	// Clear the window
	this->window->clear();

	// Check the game state
	switch (gameState)
	{
	case MENU:
		// Draw menu buttons
		this->window->draw(playButton);
		this->window->draw(exitButton);
		this->window->draw(playText);
		this->window->draw(exitText);
		break;
	case PLAYING:
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
		break;
	}

	// Display the window contents
	//this->window->display();
}


//void ChessBoard::pollEvents()
//{
//	while (this->window->pollEvent(this->event))
//	{
//		switch (this->event.type)
//		{
//		case sf::Event::Closed:
//			this->window->close();
//			break;
//		case sf::Event::MouseButtonPressed:
//			if (this->event.mouseButton.button == sf::Mouse::Left) {
//				handleMouseClick(sf::Mouse::getPosition(*window));
//			}
//			break;
//		}
//	}
//}
//
//void ChessBoard::drawBoard()
//{
//	// Calculate left and top margins
//	float leftMargin = (this->window->getSize().x - (10 * this->CellSize)) / 5;
//	float topMargin = (window->getSize().y - (8 * this->CellSize)) / 1;
//
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			// Draw board cell
//			if ((i + j) % 2 == 0)
//			{
//				board[i][j].setFillColor(sf::Color(239, 237, 209)); // Milk White
//			}
//			else
//			{
//				board[i][j].setFillColor(sf::Color(120, 150, 86)); // Green
//			}
//			float PositionX = leftMargin + j * this->CellSize, PositionY = topMargin + i * this->CellSize;
//			board[i][j].setSize(sf::Vector2f(this->CellSize, this->CellSize));
//			board[i][j].setPosition(PositionX, PositionY);
//			this->window->draw(board[i][j]);
//
//			// Draw piece sprite if there's a piece at this position
//			if (boardData[i][j] != -1)
//			{
//				sf::Sprite sprite;
//				sprite.setTexture(textures[boardData[i][j]]); // Set the texture
//				float scale = this->CellSize / static_cast<float>(textures[boardData[i][j]].getSize().x);
//				sprite.setScale(scale, scale);
//				float OffsetX = (this->CellSize - sprite.getGlobalBounds().width) / 2.0f;
//				float OffsetY = (this->CellSize - sprite.getGlobalBounds().height) / 2.0f;
//				sprite.setPosition(PositionX + OffsetX, PositionY + OffsetY);
//				window->draw(sprite);
//			}
//		}
//	}
//}

ChessBoard::GameState ChessBoard::getGameState()
{
	return gameState;
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
	// Delete board data
	for (int i = 0; i < 8; i++)
	{
		delete[] boardData[i];
	}
	delete[] boardData;

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

	// Set pointers to null
	boardData = nullptr;
	window = nullptr;
	fonts = nullptr;
}


