
#include <array>
#include <cassert>

#include "Board.h"

Board::Board() 
{
    clear();

    std::array<FigureType, 8> back_rank = {
        FigureType::Rook, FigureType::Knight, FigureType::Bishop,
        FigureType::Queen, FigureType::King, FigureType::Bishop,
        FigureType::Knight, FigureType::Rook
    };

    for (int i = 0; i < 8; ++i)
    {
        cells_[i] = Figure {back_rank[i], Color::Black};
        cells_[i+8] = Figure {FigureType::Pawn, Color::Black};
        cells_[i+56] = Figure {back_rank[i], Color::White};
        cells_[i+48] = Figure {FigureType::Pawn, Color::White};
    }
}

int Board::get_index(Coord c)
{
    assert(is_inside(c));
    return c.row * 8 + c.col;
}

Coord Board::coord_of(int index)
{
    assert(is_inside(index));
    return Coord {index / 8, index % 8};
}

// true - если внтури, false - если снаружи
bool Board::is_inside(Coord c)
{
    return 0 <= c.row && c.row < 8 && 0 <= c.col && c.col < 8;
}

bool Board::is_inside(int index)
{
    return 0 <= index && index < 64;
}

Figure Board::at(Coord c) const
{
    return cells_[get_index(c)];
}

void Board::delete_figure(Coord c)
{
    cells_[get_index(c)] = Figure {
        FigureType::None, Color::White
    };
}

void Board::add_figure(Coord c, Figure figure)
{
    cells_[get_index(c)] = figure;
}

void Board::clear()
{
    cells_.fill(Figure {
        FigureType::None, Color::White
    });
}

const std::array<Figure, 64>& Board::cells() const
{
    return cells_;
}