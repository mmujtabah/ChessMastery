#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "ChessBoard.h"


int main()
{
    ChessBoard obj;
    obj.drawMatrix();
    static sf::RectangleShape board[8][8];
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    // Extract width and height
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;
    // Create a window that fits the screen with a titlebar
    sf::RenderWindow gameWindow(desktopMode, "Chess Mastery", sf::Style::Default);
    gameWindow.setFramerateLimit(60);
    float cellSize = std::min(desktopMode.width, desktopMode.height) / 10.0f; // Calculate cell size based on screen resolution
    sf::Image icon;
    if (!icon.loadFromFile("assets/images/icon.png"))
    {
        std::cout << "Failed to load icon.ico";
        return -1;
    }
    gameWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load the image into a texture
    sf::Texture backgroundImage;
    if (!backgroundImage.loadFromFile("assets/images/BG.png"))
    {
        // Handle the case where the image cannot be loaded
        return false;
    }
    // Create a sprite and set its texture to the loaded image
    sf::Sprite backgroundSprite(backgroundImage);

    // run the program as long as the window is open
    while (gameWindow.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }
        gameWindow.draw(backgroundSprite);
        obj.drawBoard(gameWindow, board, cellSize, screenWidth, screenHeight);
        gameWindow.display();
    }

    return 0;
}