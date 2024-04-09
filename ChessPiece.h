#pragma once
#include <vector>

enum class ChessPieceState
{
    PIECE,
    CAPTURED,
    BLANK
};

struct Position
{
    int row, col;
};

class ChessPiece
{
private:
    ChessPieceState pieceState;
    std::vector<Position> validMoves;

public:
    ChessPiece(ChessPieceState state) : pieceState(state) {}

    // Getter and setter for piece state
    ChessPieceState getPieceState() const { return pieceState; }
    void setPieceState(ChessPieceState state) { pieceState = state; }

    // Add a valid move to the list
    void addValidMove(const Position &move) { validMoves.push_back(move); }

    // Clear all valid moves
    void clearValidMoves() { validMoves.clear(); }

    // Get the list of valid moves
    const std::vector<Position> &getValidMoves() const { return validMoves; }
};
