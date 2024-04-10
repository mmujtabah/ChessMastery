#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

public:
    enum class GameState
    {
        MENU,
        PLAY,
        EXIT
    };
    GameState state;
    ChessWindow();
    ~ChessWindow();
    void initWindow();
    void drawMenu();
    void drawBoard();
    void windowUpdate();
    void playSound(int index);
    void pollEvents();
    void handleMouseClick(const sf::Vector2i &mousePosition);
    bool WindowIsOpen() const;
    void renderWindow();
};