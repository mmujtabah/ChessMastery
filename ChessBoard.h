#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessPiece.h"

class ChessBoard
{
private:
	ChessPiece *board[8][8]; // The board on which the Chess is played using polymorphism
	unsigned int screenWidth;
	unsigned int screenHeight;
	int selectedPieceX;
	int selectedPieceY;
	bool endGame;
	float CellSize;
	sf::Texture **BackgroundTextures;
	sf::RenderWindow *window;
	sf::RectangleShape boardShape;
	sf::RectangleShape playButton; // Declaration of play button
	sf::RectangleShape exitButton; // Declaration of exit button
	sf::Event event;
	sf::Image Icon;
	sf::Font **fonts;		// New font for menu buttons
	sf::SoundBuffer **sound_buffer;
	sf::Text playText;		// New text for "Play" button
	sf::Text exitText;		// New text for "Exit" button
	bool playButtonPressed; // Flag to track if the "Play" button is pressed
	sf::Vector2i highlighterPosition;

public:
	ChessBoard();
	/*void drawBoard(sf::RenderWindow& window, sf::RectangleShape board[][8], float cellSize, int screenWidth, int screenHeight);*/
	enum GameState
	{
		MENU,
		PLAYING,
		GAME_OVER
	};
	GameState gameState;
	void drawBoard();
	bool WindowIsOpen() const;
	void pollEvents();
	bool EndGame() const;
	void renderWindow();
	void updateWindow();
	void initFonts();
	void initText();
	void initWindow();
	void handleKeyPress(sf::Keyboard::Key key);
	GameState getGameState();
	virtual ~ChessBoard();
};
