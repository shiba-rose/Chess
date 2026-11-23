#pragma once

#include <array>

#include "types.h"


class Board
{
public:
    Board();                                      // начальная расстановка
    Figure at(Coord c) const;
    void add_figure(Coord c, Figure f);           // заменяет, если клетка занята
    void delete_figure(Coord c);
    void clear();
    const std::array<Figure, 64>& cells() const;

    static bool  is_inside(Coord c);
    static bool  is_inside(int index);
    static Coord coord_of(int index);
    static int get_index(Coord coord);
private:
    
    std::array<Figure, 64> cells_;
};

