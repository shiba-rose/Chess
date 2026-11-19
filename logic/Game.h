#pragma once

#include <vector>

#include "types.h"
#include "Board.h"
#include "State.h"
#include "History.h"

class Game {
public:
    Game() = default;                                          // стандартная расстановка (Board::setup_standard()), ходят белые
    Game(const Board& board, const State& state);    // готовая позиция, нужна для тестов

    MoveResult         try_move(Coord from, Coord to,
                                FigureType promotion = FigureType::None);
    std::vector<Coord> legal_moves_from(Coord from) const;

    // временный метод

    void set_history(const std::vector<Move> history);

    // методы возвращающие константные ссылки
    const Board& board() const;
    const State& state() const;
    const History& history() const;
private:
    Board board_;
    State state_;
    History history_;
};
