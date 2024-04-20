#include "ChessWindow.h"
#include "ChessPiece.h"
#include <iostream>
#include <cstring>
#define WIDTH 1000
#define HEIGHT 680

ChessWindow::ChessWindow(ChessBoard &board) : state(GameState::MENU), window(nullptr), chessBoard(board), selectedPiece(nullptr), playerTurn(0)
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
        for (int i = 0; i < 6; ++i)
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

        if (mousePosition.x >= leftMargin && mousePosition.x <= rightMargin &&
            mousePosition.y >= topMargin && mousePosition.y <= bottomMargin)
        {
            int row = (mousePosition.y - topMargin) / CellSize;
            int col = (mousePosition.x - leftMargin) / CellSize;

            ChessPiece *clickedPiece = chessBoard.getPieceAt(Position(row, col));

            if (clickedPiece != nullptr)
            {

                if (!selectedPiece)
                {
                    selectedPiece = clickedPiece;

                    // Get valid moves for the selected piece
                    validMoves.clear();
                    validMoves = selectedPiece->getValidMoves(chessBoard.getBoard());
                    // Draw circles at valid moves
                    if (playerTurn == clickedPiece->getColor() || std::find(validMoves.begin(), validMoves.end(), Position(row, col)) != validMoves.end())
                    {

                        drawCircle(validMoves, leftMargin, topMargin, rightMargin, bottomMargin);
                    }
                    else
                    {
                        validMoves.clear();
                    }
                }
                else
                {
                    Position move(row, col);
                    if (std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end())
                    {
                        // Play sound based on whether a piece is moved or captured
                        if (dynamic_cast<Blank *>(chessBoard.getPieceAt(move)) == nullptr)
                        {
                            capturedPieces.push_back(clickedPiece);
                            sounds[2].play(); // Piece captured
                        }
                        else
                        {
                            sounds[1].play(); // Piece moved
                        }
                        // Move is valid, update the position of the piece on the board
                        chessBoard.movePiece(selectedPiece->getCurrentPosition(), move);
                        // Switch player turn
                        playerTurn = (playerTurn == 0) ? 1 : 0;
                        printMove(row, col);
                        chessBoard.updateBlank(const_cast<std::vector<std::vector<ChessPiece *>> &>(chessBoard.getBoard()));

                        // Clear the circles after a valid move
                        window->clear();
                        drawBoard();
                    }
                    selectedPiece = nullptr;
                }
            }
            else
            {
                // std::cout << "It's not your turn\n";
                selectedPiece = nullptr;
            }
        }
        else
        {
            // std::cout << "No piece found\n";
            selectedPiece = nullptr;
        }
    }
}

void ChessWindow::drawCircle(const std::vector<Position> &validMoves, float leftMargin, float topMargin, float rightMargin, float bottomMargin)
{
    // Calculate the size of the circle based on the cell size
    float radius = CellSize / 6;

    // Adjust the radius if the circle extends beyond the window boundaries
    float maxRadius = std::min(std::min(CellSize / 2, (rightMargin - leftMargin) / 20), (bottomMargin - topMargin) / 16);
    if (radius > maxRadius)
    {
        radius = maxRadius;
    }

    // Create the circle shape
    sf::CircleShape circle(radius);

    // Set transparency (alpha value) of the circle
    circle.setFillColor(sf::Color(0, 128, 255, 100)); // Change the last parameter (100) for transparency

    // Increase the number of points for smoother edges
    circle.setPointCount(30); // Adjust the number of points as needed

    // Iterate over each valid move and draw a circle at the corresponding position
    for (const auto &move : validMoves)
    {
        // Calculate the center position of the circle for the current move
        float centerX = leftMargin + (move.y * CellSize) + CellSize / 2;
        float centerY = topMargin + (move.x * CellSize) + CellSize / 2;

        // Position the circle
        circle.setPosition(centerX - radius, centerY - radius);

        // Draw the circle
        window->draw(circle);
    }
}

void ChessWindow::drawBoard()
{
    // Clear only the part of the window where the board is drawn
    window->clear(sf::Color::Transparent);

    // Draw the background
    sf::Sprite background(BackgroundTexture);
    window->draw(background);

    float leftMargin = (window->getSize().x - (10 * this->CellSize)) / 10, topMargin = (window->getSize().y - (9 * this->CellSize)) / 2;

    // Draw the chessboard squares
    sf::RectangleShape square(sf::Vector2f(CellSize, CellSize));
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            square.setFillColor((i + j) % 2 == 0 ? sf::Color(239, 237, 209) : sf::Color(226, 170, 35));
            float PositionX = leftMargin + j * CellSize, PositionY = topMargin + i * CellSize;
            square.setPosition(PositionX, PositionY);
            window->draw(square);

            // Draw the pieces
            ChessPiece *piece = chessBoard.getPieceAt(Position(i, j));
            if (piece != nullptr)
            {
                sf::Sprite pieceSprite(piece->texture);
                pieceSprite.setPosition(PositionX, PositionY);
                float scaleFactor = CellSize / pieceSprite.getLocalBounds().width;
                pieceSprite.setScale(scaleFactor, scaleFactor);
                window->draw(pieceSprite);
            }
        }
    }

    // Draw circles for valid moves if a piece is selected
    if (selectedPiece != nullptr)
    {
        drawCircle(validMoves, leftMargin, topMargin, leftMargin + 8 * CellSize, topMargin + 8 * CellSize);
    }

    // Draw captured pieces
    drawCapturedPieces();
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
            int gameEnd = chessBoard.checkForKingCapture();
            if (gameEnd != -1)
            {
                if (!gameEnd)
                {
                    playSound(4);
                }
                else if (gameEnd)
                {
                    playSound(5);
                }
                // Use sf::Clock to wait for 5 seconds
                sf::Clock timer;
                while (timer.getElapsedTime().asSeconds() < 5)
                {
                    // Keep polling events to ensure responsiveness
                    pollEvents();
                }
                state = GameState::EXIT;
            }
            // Check if any pawns were promoted and play sound accordingly
            if (chessBoard.promotePawns())
            {
                playSound(3);
            }
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
    std::cout << chessColumn << chessRow << " ";
}

void ChessWindow::drawCapturedPieces()
{
    sf::Text blackTitle("Black Pieces", fonts[0], 20);
    blackTitle.setFillColor(sf::Color::Green);
    sf::Text whiteTitle("White Pieces", fonts[0], 20);
    whiteTitle.setFillColor(sf::Color::Green);

    // Calculate the size of each captured piece based on the cell size
    float pieceSize = CellSize * 0.8f;

    // Calculate the position for drawing captured pieces at the extreme right of the window
    float rightMargin = window->getSize().x - pieceSize - 10.0f; // Adjust this value as needed
    float topMargin = 100.0f;                                    // Initial top margin

    // Store the size of capturedPieces to avoid recalculating it multiple times
    size_t capturedSize = capturedPieces.size();

    // Draw black pieces title
    blackTitle.setPosition(rightMargin - blackTitle.getLocalBounds().width - 80.0f, topMargin);
    window->draw(blackTitle);

    // Adjust top margin for the next drawing
    topMargin += blackTitle.getLocalBounds().height + 20.0f; // Vertical margin after the title

    // Draw black captured pieces
    int count = 0; // Counter for pieces drawn in a row
    for (size_t i = 0; i < capturedSize; ++i)
    {
        ChessPiece *piece = capturedPieces[i];
        if (piece->getColor()) // Check if the piece is black
        {
            sf::Sprite pieceSprite(piece->texture);
            int row = count / 5; // 5 pieces per row
            int col = count % 5;
            float xPos = rightMargin - (col + 1) * pieceSize;
            float yPos = topMargin + row * pieceSize;
            pieceSprite.setPosition(xPos, yPos);
            float scaleFactor = pieceSize / pieceSprite.getLocalBounds().width;
            pieceSprite.setScale(scaleFactor, scaleFactor);
            window->draw(pieceSprite);

            ++count;
        }
    }

    // Adjust top margin for the next drawing
    topMargin += ((count - 1) / 5 + 1) * pieceSize + 80.0f; // Vertical margin after drawing black pieces

    // Draw white pieces title
    whiteTitle.setPosition(rightMargin - whiteTitle.getLocalBounds().width - 80.0f, topMargin + 80);
    window->draw(whiteTitle);

    // Adjust top margin for the next drawing
    topMargin += whiteTitle.getLocalBounds().height + 100.0f; // Vertical margin after the title

    // Draw white captured pieces
    count = 0; // Reset counter for pieces drawn in a row
    for (size_t i = 0; i < capturedSize; ++i)
    {
        ChessPiece *piece = capturedPieces[i];
        if (!piece->getColor()) // Check if the piece is white
        {
            sf::Sprite pieceSprite(piece->texture);
            int row = count / 5; // 5 pieces per row
            int col = count % 5;
            float xPos = rightMargin - (col + 1) * pieceSize;
            float yPos = topMargin + row * pieceSize;
            pieceSprite.setPosition(xPos, yPos);
            float scaleFactor = pieceSize / pieceSprite.getLocalBounds().width;
            pieceSprite.setScale(scaleFactor, scaleFactor);
            window->draw(pieceSprite);

            ++count;
        }
    }
}

ChessWindow::~ChessWindow()
{
    if (window != nullptr)
    {
        delete window;
        window = nullptr;
    }
}