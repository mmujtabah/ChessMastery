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
}
