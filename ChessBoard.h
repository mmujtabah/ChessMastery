#pragma once++

class ChessBoard
{
private: 
int ** boardData;
sf::Texture textures[12];

public:
	ChessBoard();
	virtual ~ChessBoard();
	void drawBoard(sf::RenderWindow& window, sf::RectangleShape board[][8], float cellSize, int screenWidth, int screenHeight);
	void drawMatrix();
};