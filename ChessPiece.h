#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
enum class ChessPieceState
{
    PIECE,
    CAPTURED,
    BLANK
};

struct Position
{
    int x, y;
};

class ChessPiece
{
private:
    ChessPieceState pieceState;
    std::vector<Position> validMoves;
    bool color; // White : 0, Black : 1
    sf::Texture texture;

public:
    ChessPiece(ChessPieceState state, bool color) : pieceState(state), color(color) {}

    // Getter and setter for piece state
    ChessPieceState getPieceState() const { return pieceState; }
    virtual void setPieceState(ChessPieceState state) { pieceState = state; }

    // Add a valid move to the list
    virtual void addValidMove(const Position &move) { validMoves.push_back(move); }

    // Clear all valid moves
    void clearValidMoves() { validMoves.clear(); }

    // Get the list of valid moves
    virtual const std::vector<Position> &getValidMoves() const { return validMoves; }

    virtual void setTexture();
};

class King : public ChessPiece
{
private:
public:
    King();
    ~King();
};

class Queen : public ChessPiece
{
private:
public:
    Queen();
    ~Queen();
};

class Rook : public ChessPiece
{
private:
public:
    Rook();
    ~Rook();
};

class Bishop : public ChessPiece
{
private:
public:
    Bishop();
    ~Bishop();
};

class Knight : public ChessPiece
{
    private:
    public:
    Knight();
    ~Knight();
};

class Pawn : public ChessPiece
{
    
};
