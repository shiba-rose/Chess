#pragma once

#include <optional>
#include <vector>

#include "types.h"

struct State {
    Color               current_move = Color::White;
    GameStatus          status = GameStatus::InProgress;
    std::vector<Figure> captured_figures;      // для панели съеденных

    // рокировка: ходили ли король и ладьи (ладьи a и h различаются)
    bool white_king_moved = false, black_king_moved = false;
    bool white_rook_a_moved = false, white_rook_h_moved = false;
    bool black_rook_a_moved = false, black_rook_h_moved = false;

    // взятие на проходе: клетка, через которую только что прошла пешка
    std::optional<Coord> en_passant_target;

    // ничья по длине партии: растёт после каждого полухода, при 300 будет Draw
    int ply_count = 0;
};
