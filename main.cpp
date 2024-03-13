#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "Pawn.h"
void drawBoard(sf::RenderWindow& window, int boardData[][8], sf::RectangleShape board[][8])
{
	static const float cellSize = 62.0f;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sf::Sprite sprite;
			board[i][j].setSize(sf::Vector2f(cellSize, cellSize));
			board[i][j].setPosition((i + 7.9) * cellSize, (j + 0.2) * cellSize);
			if ((i + j) % 2 == 0)
			{
				board[i][j].setFillColor(sf::Color(239, 237, 209)); // Milk White
			}
			else
			{
				board[i][j].setFillColor(sf::Color(120, 150, 86)); // Green
			}
			window.draw(board[i][j]);
		}
	}
}
int main()
{
    int boardData[8][8]{ 0 };
    static sf::RectangleShape board[8][8];
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Create a window that fits the screen with a titlebar
    sf::RenderWindow window(desktopMode, "Chess Mastery", sf::Style::Default);

    window.setFramerateLimit(60);
    sf::Image icon;
    if (!icon.loadFromFile("icon.png"))
    {
        std::cout << "Failed to load icon.ico";
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // run the program as long as the window is open
    while (window.isOpen())
    {
		drawBoard(window, boardData, board);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }

    return 0;
}
