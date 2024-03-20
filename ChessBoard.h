#pragma once++
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class ChessBoard
{
private:
	int** boardData;
	unsigned int screenWidth;
	unsigned int screenHeight;
	bool endGame;
	float CellSize;
	sf::Texture textures[12];
	sf::RenderWindow* window;
	sf::VideoMode desktopMode;
	sf::RectangleShape board[8][8];
	sf::Event event;
	sf::Image Icon;
public:
	ChessBoard();
	/*void drawBoard(sf::RenderWindow& window, sf::RectangleShape board[][8], float cellSize, int screenWidth, int screenHeight);*/
	void drawBoard();
	void drawMatrix();
	bool WindowIsOpen() const;
	void pollEvents();
	bool EndGame() const;
	void renderWindow();
	void updateWindow();
	void initFonts();
	void initText();
	void initWindow();
	virtual ~ChessBoard();
};