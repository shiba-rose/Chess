#pragma once

#include "types.h"



struct Move {
    Coord      from, to, enpassant = {0, 0};
    MoveKind   kind = MoveKind::Turn;
    Figure promtion = {};
};