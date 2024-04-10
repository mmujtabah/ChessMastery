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
protected:
    ChessPieceState pieceState;
    std::vector<Position> validMoves;
    bool color; // White : 0, Black : 1
    sf::Texture texture;

public:
    ChessPiece(ChessPieceState state, bool color) : pieceState(state), color(color) {}

    // Getter and setter for piece state
    ChessPieceState getPieceState() const { return pieceState; }
    // virtual void setPieceState(ChessPieceState state) { pieceState = state; }

    // Add a valid move to the list
    // virtual void addValidMove(const Position &move) { validMoves.push_back(move); }

    // Clear all valid moves
    void clearValidMoves() { validMoves.clear(); }

    // Get the list of valid moves
    const std::vector<Position> &getValidMoves() const { return validMoves; }

    virtual void setTexture() = 0;
    bool getColor() { return color; };

    virtual ~ChessPiece();
};

class King : public ChessPiece
{
private:
public:
    King(ChessPieceState state, bool color) : ChessPiece(state, color) { setTexture(); }
    ~King();
    void setTexture() override;
};

class Queen : public ChessPiece
{
private:
public:
    Queen(ChessPieceState state, bool color) : ChessPiece(state, color) { setTexture(); }
    ~Queen();
    void setTexture() override;
};

class Rook : public ChessPiece
{
private:
public:
    Rook(ChessPieceState state, bool color) : ChessPiece(state, color) { setTexture(); }
    ~Rook();
    void setTexture() override;
};

class Bishop : public ChessPiece
{
private:
public:
    Bishop(ChessPieceState state, bool color) : ChessPiece(state, color) { setTexture(); }
    ~Bishop();
    void setTexture() override;
};

class Knight : public ChessPiece
{
private:
public:
    Knight(ChessPieceState state, bool color) : ChessPiece(state, color) { setTexture(); }
    ~Knight();
    void setTexture() override;
};

class Pawn : public ChessPiece
{
private:
public:
    Pawn(ChessPieceState state, bool color) : ChessPiece(state, color) { setTexture(); }
    ~Pawn();
    void setTexture() override;
};
