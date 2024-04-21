#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
enum class ChessPieceState
{
    PIECE,
    CAPTURED,
    BLANK
};

struct Position
{
    int x, y;
    Position(int _x, int _y) : x(_x), y(_y) {}
    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

class ChessPiece
{
protected:
    ChessPieceState pieceState;
    std::vector<Position> validMoves;
    bool color; // White : 0, Black : 1
    Position currentPosition;

public:
    ChessPiece(bool color, int x, int y) : color(color), currentPosition({x, y}) {}

    // Getter and setter for piece state
    ChessPieceState getPieceState() const { return pieceState; }
    void setPieceState(ChessPieceState state) { pieceState = state; }

    // Add a valid move to the list
    void addValidMove(const Position &move) { validMoves.push_back(move); }

    // Get valid moves
    virtual std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const = 0;

    // Clear all valid moves
    void clearValidMoves() { validMoves.clear(); }

    virtual void setTexture() = 0;
    bool getColor() const { return color; };

    // Getter and setter for current position
    Position getCurrentPosition() const { return currentPosition; }
    void setCurrentPosition(const Position &pos) { currentPosition = pos; }

    bool isOnBoard(const Position &pos) const
    {
        return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
    }
    sf::Texture texture;
    void capture() { pieceState = ChessPieceState::CAPTURED; } // Update state to CAPTURED

    virtual ~ChessPiece();
};

class King : public ChessPiece
{
private:
public:
    King(bool color, int x, int y) : ChessPiece(color, x, y)
    {
        pieceState = ChessPieceState::PIECE;
        setTexture();
    }
    ~King();
    void setTexture() override;
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override;
};

class Queen : public ChessPiece
{
private:
public:
    Queen(bool color, int x, int y) : ChessPiece(color, x, y)
    {
        pieceState = ChessPieceState::PIECE;
        setTexture();
    }
    ~Queen();
    void setTexture() override;
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override;
};

class Rook : public ChessPiece
{
private:
public:
    Rook(bool color, int x, int y) : ChessPiece(color, x, y)
    {
        pieceState = ChessPieceState::PIECE;
        setTexture();
    }
    ~Rook();
    void setTexture() override;
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override;
};

class Bishop : public ChessPiece
{
private:
public:
    Bishop(bool color, int x, int y) : ChessPiece(color, x, y)
    {
        pieceState = ChessPieceState::PIECE;
        setTexture();
    }
    ~Bishop();
    void setTexture() override;
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override;
};

class Knight : public ChessPiece
{
private:
public:
    Knight(bool color, int x, int y) : ChessPiece(color, x, y)
    {
        pieceState = ChessPieceState::PIECE;
        setTexture();
    }
    ~Knight();
    void setTexture() override;
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override;
};

class Pawn : public ChessPiece
{
private:
public:
    Pawn(bool color, int x, int y) : ChessPiece(color, x, y)
    {
        pieceState = ChessPieceState::PIECE;
        setTexture();
    }
    ~Pawn();
    void setTexture() override;
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override;
};

class Blank : public ChessPiece
{
private:
public:
    Blank(bool color = 0, int x = 0, int y = 0) : ChessPiece(color, x, y) { pieceState = ChessPieceState::BLANK; }
    ~Blank() {}
    std::vector<Position> getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const override { return {}; }
    void setTexture() override {}
};

class ChessBoard
{
private:
    std::vector<std::vector<ChessPiece *>> board;

public:
    ChessBoard();
    ~ChessBoard();
    // Getter for the board
    const std::vector<std::vector<ChessPiece *>> &getBoard() const { return board; }
    // Function to move a piece on the board
    void movePiece(const Position &from, const Position &to);
    // Function to get a piece at a specific position on the board
    ChessPiece *getPieceAt(const Position &pos) const;
    void updateBlank(std::vector<std::vector<ChessPiece *>> &board) const;
    bool promotePawns();
    bool checkForKingCapture();
};
