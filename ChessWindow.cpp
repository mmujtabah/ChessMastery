#include "ChessWindow.h"
#include "ChessPiece.h"
#include <iostream>
#define WIDTH 1000
#define HEIGHT 680

ChessWindow::ChessWindow(ChessBoard &board) : state(GameState::MENU), window(nullptr), chessBoard(board), selectedPiece(nullptr)
{
    initWindow();
}

void ChessWindow::initWindow()
{
    if (window == nullptr)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 16; // Adjust the level as needed
        window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Chess Mastery", sf::Style::Close | sf::Style::Titlebar, settings);
        window->setFramerateLimit(60);
        width = window->getSize().x;
        height = window->getSize().y;
        CellSize = std::min(width, height) / 10.0f;
        // Load Icon
        if (!Icon.loadFromFile("assets/images/icon.png"))
        {
            std::cerr << "Failed to load icon file";
        }
        window->setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
        // Load Sounds
        for (int i = 0; i < 4; ++i)
        {
            std::string fileName = "assets/sounds/sound" + std::to_string(i) + ".wav";
            if (!sound_buffers[i].loadFromFile(fileName))
            {
                std::cerr << "Failed to load sound file " << fileName << "!" << std::endl;
            }
            else
            {
                // Associate sound buffers with sound objects
                sounds[i].setBuffer(sound_buffers[i]);
            }
        }
        // Load Backgrounds
        if (!BackgroundTexture.loadFromFile("assets/images/bg.jpg"))
        {
            std::cerr << "Failed to load font "
                      << "assets/images/bg.jpg"
                      << "!" << std::endl;
        }
        // Load fonts into the fonts array
        for (int i = 0; i < 2; ++i)
        {
            std::string fontFilename = "assets/fonts/" + std::to_string(i) + ".ttf";
            if (!fonts[i].loadFromFile(fontFilename))
            {
                std::cerr << "Failed to load font " << fontFilename << "!" << std::endl;
            }
        }
    }
}

void ChessWindow::drawMenu()
{
    // Clear the window
    window->clear();

    // Draw background
    sf::Sprite background(BackgroundTexture);
    window->draw(background);

    // Load play and exit button textures
    sf::Texture playButtonTexture, exitButtonTexture;
    if (!playButtonTexture.loadFromFile("assets/images/play.png"))
    {
        std::cerr << "Failed to load play button texture!" << std::endl;
        // Handle error
    }
    if (!exitButtonTexture.loadFromFile("assets/images/exit.png"))
    {
        std::cerr << "Failed to load exit button texture!" << std::endl;
        // Handle error
    }

    // Create sprites for play and exit buttons
    playButton.setTexture(playButtonTexture);
    exitButton.setTexture(exitButtonTexture);

    // Calculate positions based on window size
    sf::Vector2u windowSize = window->getSize();
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;
    float margin = 70.0f;     // Adjust margin as needed
    float buttonSize = 40.0f; // Adjust button size as needed

    // Calculate total height of buttons
    float totalButtonHeight = 2 * buttonSize + margin;

    // Position the buttons vertically centered with a margin between them
    playButton.setPosition(centerX - playButton.getLocalBounds().width / 4, centerY - totalButtonHeight / 2);
    exitButton.setPosition(centerX - exitButton.getLocalBounds().width / 4, centerY + margin + buttonSize - totalButtonHeight / 2);

    // Adjust the scale of the buttons to make them smaller
    float scale = 0.5f; // Adjust scale factor as needed
    playButton.setScale(scale, scale);
    exitButton.setScale(scale, scale);

    // Draw buttons
    window->draw(playButton);
    window->draw(exitButton);
}

void ChessWindow::pollEvents()
{
    while (window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            state = GameState::EXIT;
            break;
        case sf::Event::MouseButtonPressed:
            if (this->event.mouseButton.button == sf::Mouse::Left)
            {
                handleMouseClick(sf::Mouse::getPosition(*window));
            }
            break;
        }
    }
}

void ChessWindow::handleMouseClick(const sf::Vector2i &mousePosition)
{
    if (state == GameState::MENU)
    {
        if (playButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {
            sounds[0].play();
            state = GameState::PLAY;
        }
        else if (exitButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        {
            state = GameState::EXIT;
        }
    }
    else if (state == GameState::PLAY)
    {
        float leftMargin = (window->getSize().x - (10 * this->CellSize)) / 10;
        float topMargin = (window->getSize().y - (9 * this->CellSize)) / 2;
        float rightMargin = leftMargin + 8 * this->CellSize;
        float bottomMargin = topMargin + 8 * this->CellSize;

        // Check if the click falls within the bounds of the chessboard
        if (mousePosition.x >= leftMargin && mousePosition.x <= rightMargin &&
            mousePosition.y >= topMargin && mousePosition.y <= bottomMargin)
        {
            // Calculate row and column indices of the clicked cell
            int row = (mousePosition.y - topMargin) / CellSize;
            int col = (mousePosition.x - leftMargin) / CellSize;

            // Print the indices
            std::cout << "Clicked cell: Row = " << row << ", Column = " << col << std::endl;
            // Get the chess piece at the clicked cell
            ChessPiece *clickedPiece = chessBoard.getPieceAt(Position(row, col));

            if (clickedPiece != nullptr)
            {
                // Piece exists at the clicked cell
                if (!selectedPiece)
                {
                    // If no piece is selected, select the clicked piece
                    selectedPiece = clickedPiece;
                    std::cout << "Selected Piece: \n";
                }
                else
                {
                    // If a piece is already selected, attempt to move it to the clicked cell
                    Position move(row, col);
                    if (selectedPiece->ValidMove(move, chessBoard.getBoard()))
                    {
                        // Move is valid, update the position of the piece on the board
                        chessBoard.movePiece(selectedPiece->getCurrentPosition(), move);
                        printMove(row, col);
                        chessBoard.updateBlank(const_cast<std::vector<std::vector<ChessPiece *>> &>(chessBoard.getBoard()));
                    }
                    else
                    {
                        // Move is invalid, notify the player
                        std::cout << "Invalid move for \n";
                    }

                    // Deselect the piece after attempting the move
                    selectedPiece = nullptr;
                }
            }
            else
            {
                // Clicked cell is empty, deselect any selected piece
                selectedPiece = nullptr;
            }
        }
    }
}

void ChessWindow::drawBoard()
{
    // Clear the window
    window->clear();

    // Draw background
    sf::Sprite background(BackgroundTexture);
    window->draw(background);
    float leftMargin = (window->getSize().x - (10 * this->CellSize)) / 10, topMargin = (window->getSize().y - (9 * this->CellSize)) / 2;
    // Draw the chessboard
    sf::RectangleShape square(sf::Vector2f(CellSize, CellSize));
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            square.setFillColor((i + j) % 2 == 0 ? sf::Color(239, 237, 209) : sf::Color(226, 170, 35)); // Alternating colors for chessboard
            float PositionX = leftMargin + j * CellSize, PositionY = topMargin + i * CellSize;
            square.setPosition(PositionX, PositionY); // Adjust position based on parameters
            window->draw(square);

            // Draw the pieces
            ChessPiece *piece = chessBoard.getPieceAt(Position(i, j));
            if (piece != nullptr)
            {
                sf::Sprite pieceSprite(piece->texture);
                pieceSprite.setPosition(PositionX, PositionY);
                // Adjust the scale of the piece
                float scaleFactor = CellSize / pieceSprite.getLocalBounds().width;
                pieceSprite.setScale(scaleFactor, scaleFactor);
                window->draw(pieceSprite);
            }
        }
    }
}

void ChessWindow::windowUpdate()
{
    while (window->isOpen() && state != GameState::EXIT)
    {
        if (state == GameState::MENU)
        {
            drawMenu();
        }
        else if (state == GameState::PLAY)
        {
            drawBoard();
        }
        pollEvents();

        if (state == GameState::EXIT)
        {
            window->close();
        }

        renderWindow();
    }
}

bool ChessWindow::WindowIsOpen() const
{
    if (window != nullptr)
    {
        return window->isOpen();
    }
    else
    {
        std::cout << "Window not initialized\n";
        return false;
    }
}

void ChessWindow::renderWindow()
{
    window->display();
}

void ChessWindow::playSound(int index)
{
    sounds[index].play();
}

#include <iostream>
#include <string>

void ChessWindow::printMove(int row, int col)
{
    // Convert column index to chess notation (a-h)
    std::string chessColumn;
    switch (col)
    {
    case 0:
        chessColumn = "a";
        break;
    case 1:
        chessColumn = "b";
        break;
    case 2:
        chessColumn = "c";
        break;
    case 3:
        chessColumn = "d";
        break;
    case 4:
        chessColumn = "e";
        break;
    case 5:
        chessColumn = "f";
        break;
    case 6:
        chessColumn = "g";
        break;
    case 7:
        chessColumn = "h";
        break;
    default:
        chessColumn = "?";
        break;
    }

    // Convert row index to chess notation (1-8)
    int chessRow = 8 - row;

    // Print the chess notation move
    std::cout << "Chess Notation Move: " << chessColumn << chessRow << std::endl;
}

ChessWindow::~ChessWindow()
{
    if (window != nullptr)
    {
        delete window;
        window = nullptr;
    }
}