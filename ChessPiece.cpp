#include "ChessPiece.h"
#include <iostream>

ChessPiece::~ChessPiece() {}

King::~King() {}

Queen::~Queen() {}

Rook::~Rook() {}

Bishop::~Bishop() {}

Knight::~Knight() {}

Pawn::~Pawn() {}

void King::setTexture()
{
    if (getColor() == 0)
    {
        if (!texture.loadFromFile("assets/images/wk.png"))
        {
            std::cerr << "Failed to load texture: "
                      << "assets/images/wk.png" << std::endl;
        }
    }
    else if (getColor() == 1)
    {
        if (!texture.loadFromFile("assets/images/bk.png"))
        {
            std::cerr << "Failed to load texture: "
                      << "assets/images/bk.png" << std::endl;
        }
    }
    texture.setSmooth(true);
}

void Queen::setTexture()
{
    if (getColor() == 0)
    {
        if (!texture.loadFromFile("assets/images/wq.png"))
        {
            std::cerr << "Failed to load texture: assets/images/wq.png" << std::endl;
        }
    }
    else if (getColor() == 1)
    {
        if (!texture.loadFromFile("assets/images/bq.png"))
        {
            std::cerr << "Failed to load texture: assets/images/bq.png" << std::endl;
        }
    }
    texture.setSmooth(true);
}

void Rook::setTexture()
{
    if (getColor() == 0)
    {
        if (!texture.loadFromFile("assets/images/wr.png"))
        {
            std::cerr << "Failed to load texture: assets/images/wr.png" << std::endl;
        }
    }
    else if (getColor() == 1)
    {
        if (!texture.loadFromFile("assets/images/br.png"))
        {
            std::cerr << "Failed to load texture: assets/images/br.png" << std::endl;
        }
    }
    texture.setSmooth(true);
}

void Bishop::setTexture()
{
    if (getColor() == 0)
    {
        if (!texture.loadFromFile("assets/images/wb.png"))
        {
            std::cerr << "Failed to load texture: assets/images/wb.png" << std::endl;
        }
    }
    else if (getColor() == 1)
    {
        if (!texture.loadFromFile("assets/images/bb.png"))
        {
            std::cerr << "Failed to load texture: assets/images/bb.png" << std::endl;
        }
    }
    texture.setSmooth(true);
}

void Knight::setTexture()
{
    if (getColor() == 0)
    {
        if (!texture.loadFromFile("assets/images/wn.png"))
        {
            std::cerr << "Failed to load texture: assets/images/wn.png" << std::endl;
        }
    }
    else if (getColor() == 1)
    {
        if (!texture.loadFromFile("assets/images/bn.png"))
        {
            std::cerr << "Failed to load texture: assets/images/bn.png" << std::endl;
        }
    }
    texture.setSmooth(true);
}

void Pawn::setTexture()
{
    if (getColor() == 0)
    {
        if (!texture.loadFromFile("assets/images/wp.png"))
        {
            std::cerr << "Failed to load texture: assets/images/wp.png" << std::endl;
        }
    }
    else if (getColor() == 1)
    {
        if (!texture.loadFromFile("assets/images/bp.png"))
        {
            std::cerr << "Failed to load texture: assets/images/bp.png" << std::endl;
        }
    }
    texture.setSmooth(true);
}

bool King::ValidMove(const Position &move, const std::vector<std::vector<ChessPiece *>> &board) const
{
    int dx = move.x - getCurrentPosition().x;
    int dy = move.y - getCurrentPosition().y;
    return (abs(dx) <= 1 && abs(dy) <= 1);
}

bool Queen::ValidMove(const Position &move, const std::vector<std::vector<ChessPiece *>> &board) const
{
    return false;
}

bool Rook::ValidMove(const Position &move, const std::vector<std::vector<ChessPiece *>> &board) const
{
    return false;
}

bool Bishop::ValidMove(const Position &move, const std::vector<std::vector<ChessPiece *>> &board) const
{
    return false;
}

bool Knight::ValidMove(const Position &move, const std::vector<std::vector<ChessPiece *>> &board) const
{
    return false;
}

bool Pawn::ValidMove(const Position &move, const std::vector<std::vector<ChessPiece *>> &board) const
{
    // Get the current position of the pawn
    Position currentPos = getCurrentPosition();

    // Determine the direction of movement based on the pawn's color
    int direction = getColor() ? -1 : 1; // For white pawns, move up (decrease y), for black pawns, move down (increase y)

    // Check if the move is one step forward
    if (move.x == currentPos.x && move.y == currentPos.y + direction)
    {
        // Check if the destination square is empty
        if (dynamic_cast<Blank *>(board[move.x][move.y]) != nullptr)
        {
            return true; // Valid move: empty square ahead
        }
    }
    // Check if the pawn is making its initial double-step move
    else if (currentPos.y == 1 && move.x == currentPos.x && move.y == currentPos.y + 2 * direction)
    {
        // Check if both the destination square and the square in between are empty
        if (board[move.x][move.y] == nullptr && board[currentPos.x][currentPos.y + direction] == nullptr)
        {
            return true; // Valid move: empty squares ahead
        }
    }
    // Check if the pawn is capturing diagonally
    else if (abs(move.x - currentPos.x) == 1 && move.y == currentPos.y + direction)
    {
        // Check if there is an opponent's piece to capture
        ChessPiece *targetPiece = board[move.x][move.y];
        if (targetPiece != nullptr && targetPiece->getColor() != getColor() && dynamic_cast<Blank *>(targetPiece) == nullptr)
        {
            return true; // Valid move: capturing an opponent's piece diagonally
        }
    }

    // If none of the conditions are met, the move is not valid
    return false;
}

// Implementation of getPieceAt member function
ChessPiece *ChessBoard::getPieceAt(const Position &pos) const
{
    // Check if the position is within the board boundaries
    if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8)
    {
        return board[pos.x][pos.y];
    }
    else
    {
        // Return nullptr if the position is out of bounds
        return nullptr;
    }
}

ChessBoard::ChessBoard()
{
    // Initialize the board with nullptrs
    board.resize(8, std::vector<ChessPiece *>(8, nullptr));

    // Add black pieces
    board[0][0] = new Rook(1, 0, 0);
    board[0][1] = new Knight(1, 0, 1);
    board[0][2] = new Bishop(1, 0, 2);
    board[0][3] = new Queen(1, 0, 3);
    board[0][4] = new King(1, 0, 4);
    board[0][5] = new Bishop(1, 0, 5);
    board[0][6] = new Knight(1, 0, 6);
    board[0][7] = new Rook(1, 0, 7);

    // Add black pawns...
    for (int i = 0; i < 8; i++)
        board[1][i] = new Pawn(1, 1, i);

    // Add white pieces
    board[7][0] = new Rook(0, 0, 0);
    board[7][1] = new Knight(0, 0, 1);
    board[7][2] = new Bishop(0, 0, 2);
    board[7][3] = new Queen(0, 0, 3);
    board[7][4] = new King(0, 0, 4);
    board[7][5] = new Bishop(0, 0, 5);
    board[7][6] = new Knight(0, 0, 6);
    board[7][7] = new Rook(0, 0, 7);

    // Add white pawns...
    for (int i = 0; i < 8; i++)
        board[6][i] = new Pawn(0, 1, i);

    // Add blank pieces
    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = new Blank(0, i, j);
}

ChessBoard::~ChessBoard()
{
    // Delete all pieces
    for (auto &row : board)
    {
        for (auto &piece : row)
        {
            delete piece;
        }
    }
    board.clear();
}

void ChessBoard::movePiece(const Position &from, const Position &to)
{
    ChessPiece *pieceToMove = board[from.x][from.y];
    if (pieceToMove && pieceToMove->ValidMove(to, board))
    {
        // Valid move, update the board
        board[to.x][to.y] = pieceToMove;
        board[from.x][from.y] = nullptr;
        pieceToMove->setCurrentPosition(to);
    }
}