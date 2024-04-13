#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ChessPiece.h"
class ChessWindow
{
private:
    sf::RenderWindow *window;
    unsigned int width, height;
    float CellSize;
    sf::Texture BackgroundTexture;
    sf::Sprite playButton, exitButton;
    sf::Event event;
    sf::Image Icon;
    sf::Font fonts[2];
    sf::SoundBuffer sound_buffers[4];
    sf::Sound sounds[4];
    bool windowOpen;
    bool playerTurn;
    ChessBoard &chessBoard;
    ChessPiece *selectedPiece;
    std::vector<Position> validMoves;
public:
    enum class GameState
    {
        MENU,
        PLAY,
        EXIT
    };
    GameState state;
    ChessWindow(ChessBoard &board);
    ~ChessWindow();
    void initWindow();
    void drawMenu();
    void drawBoard();
    void printMove(int row, int col);
    void drawCircle(const std::vector<Position> &validMoves, float leftMargin, float topMargin, float rightMargin, float bottomMargin);
    void windowUpdate();
    void playSound(int index);
    void pollEvents();
    void handleMouseClick(const sf::Vector2i &mousePosition);
    bool WindowIsOpen() const;
    void renderWindow();
};