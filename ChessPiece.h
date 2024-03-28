#pragma once
#include <SFML/Graphics.hpp>

class ChessPiece // abstact base class whose pointer is to be created
{
protected:
    bool move; // For checking whether the piece has moved or not
    int x, y, value;
    bool color; // 1 for white, 0 for black
public:
    enum PieceState
    {
        BLANK,
        PIECE,
        CAPTURED
    };
    PieceState State;
    sf::Texture textures; // Add this member variable
    sf::Sprite sprite;
    virtual bool isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece *board[8][8]); // Every derived class has its own unique function
    ChessPiece(bool color, int x, int y, int value);
    void setPosition(int x, int y);
    int getX();
    int getY();
    int getValue();
    void Print(int x, int y);
    virtual PieceState getPieceState() = 0;
    ~ChessPiece();
};
