#pragma once

#include "types.h"

enum class MoveKind { Turn, Break, Castling, EnPassant  };

struct Move {
    Coord      from, to;
    MoveKind   kind = MoveKind::Turn;
    FigureType main_figure = FigureType::None;
    FigureType minor_figure = FigureType::None;
    bool check = false;
};