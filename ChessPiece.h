#pragma once
#include <SFML/Graphics.hpp>

class ChessPiece // abstact base class whose pointer is to be created
{
protected:
    int move;   // For checking whether the piece has moved or not
    bool color; // 1 for white, 0 for black

public:
    enum PieceState
    {
        BLANK,
        PIECE
    };
    PieceState State;
    sf::Texture textures; // Add this member variable
    sf::Sprite sprite;
    // virtual bool isValid(int xfrom, int yfrom, int xto, int yto, ChessPiece* b[8][8]); // Every derived class has its own unique function
    ChessPiece();
    void Print(int x, int y);
    virtual PieceState getPieceState() = 0;
    ~ChessPiece();
};
