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

std::vector<Position> King::getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const
{
    std::vector<Position> validMoves;

    // Implement logic to calculate valid moves for the king

    return validMoves;
}

std::vector<Position> Queen::getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const
{
    std::vector<Position> validMoves;

    // Implement logic to calculate valid moves for the queen

    return validMoves;
}

std::vector<Position> Rook::getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const
{
    std::vector<Position> validMoves;

    // Define the directions in which the rook can move (vertical and horizontal)
    std::vector<Position> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // Check each direction
    for (const auto &dir : directions)
    {
        // Start from the rook's current position
        Position currentPosition = getCurrentPosition();

        // Move in the current direction until reaching the edge of the board or encountering a piece
        while (true)
        {
            // Move to the next position in the direction
            currentPosition.x += dir.x;
            currentPosition.y += dir.y;

            // Check if the new position is on the board
            if (!isOnBoard(currentPosition))
                break;

            // Get the piece at the new position
            ChessPiece *targetPiece = board[currentPosition.x][currentPosition.y];

            // If the position is empty, add it as a valid move
            if (dynamic_cast<Blank *>(targetPiece) != nullptr)
            {
                validMoves.push_back(currentPosition);
            }
            // If the position contains an opponent's piece, add it as a valid move and stop searching in this direction
            else if (targetPiece->getColor() != getColor())
            {
                validMoves.push_back(currentPosition);
                break;
            }
            // If the position contains the player's own piece, stop searching in this direction
            else
            {
                break;
            }
        }
    }

    return validMoves;
}

std::vector<Position> Bishop::getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const
{
    std::vector<Position> validMoves;

    // Implement logic to calculate valid moves for the bishop

    return validMoves;
}

std::vector<Position> Knight::getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const
{
    std::vector<Position> validMoves;

    // Implement logic to calculate valid moves for the knight

    return validMoves;
}

std::vector<Position> Pawn::getValidMoves(const std::vector<std::vector<ChessPiece *>> &board) const
{
    std::vector<Position> validMoves;

    // Determine the direction of movement based on the pawn's color
    int direction = (getColor() == 0) ? -1 : 1; // For white pawns, move up (decrease y), for black pawns, move down (increase y)

    // Check one square forward
    Position forwardOne(getCurrentPosition().x + direction, getCurrentPosition().y);
    if (isOnBoard(forwardOne) && dynamic_cast<Blank *>(board[forwardOne.x][forwardOne.y]) != nullptr)
    {
        validMoves.push_back(forwardOne);

        // Check two squares forward if pawn hasn't moved yet
        if ((getColor() == 0 && getCurrentPosition().x == 6) || (getColor() == 1 && getCurrentPosition().x == 1))
        {
            Position forwardTwo(getCurrentPosition().x + 2 * direction, getCurrentPosition().y);
            if (dynamic_cast<Blank *>(board[forwardTwo.x][forwardTwo.y]) != nullptr)
            {
                validMoves.push_back(forwardTwo);
            }
        }
    }

    // Check diagonal captures
    std::vector<Position> diagonalMoves = {{direction, -1}, {direction, 1}};
    for (const auto &move : diagonalMoves)
    {
        Position target(getCurrentPosition().x + move.x, getCurrentPosition().y + move.y);
        if (isOnBoard(target))
        {
            ChessPiece *targetPiece = board[target.x][target.y];
            // Ensure the target position is not empty and contains an opponent's piece
            if (dynamic_cast<Blank *>(targetPiece) == nullptr && targetPiece->getColor() != getColor())
            {
                validMoves.push_back(target);
            }
        }
    }

    return validMoves;
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
    board[7][0] = new Rook(0, 7, 0);
    board[7][1] = new Knight(0, 7, 1);
    board[7][2] = new Bishop(0, 0, 2);
    board[7][3] = new Queen(0, 7, 3);
    board[7][4] = new King(0, 7, 4);
    board[7][5] = new Bishop(0, 7, 5);
    board[7][6] = new Knight(0, 7, 6);
    board[7][7] = new Rook(0, 7, 7);

    // Add white pawns...
    for (int i = 0; i < 8; i++)
        board[6][i] = new Pawn(0, 6, i);

    // Add blank pieces
    updateBlank(board);
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
    std::vector<Position> validMoves = pieceToMove->getValidMoves(board); // Get valid moves for the piece
    if (pieceToMove && std::find(validMoves.begin(), validMoves.end(), to) != validMoves.end())
    {
        // Valid move, update the board
        board[to.x][to.y] = pieceToMove;
        board[from.x][from.y] = nullptr;
        pieceToMove->setCurrentPosition(to);
    }
}

void ChessBoard::updateBlank(std::vector<std::vector<ChessPiece *>> &board) const
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] == nullptr)
            {
                // If the cell is empty, initialize a new Blank object and assign it
                board[i][j] = new Blank(0, i, j);
            }
        }
    }
}
