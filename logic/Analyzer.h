
#include <vector>

#include "move.h"
#include "board.h"
#include "state.h"
#include "types.h"

// Интерфейс Анализатора

namespace Analyzer
{
    // Функции поиска хода
    Move get_correct_move(const Board&, const State&, Coord c1, Coord c2);
    std::vector<Coord> get_legal_moves(const Board&, const State&, Coord c1);
    
    // Функции анализа позиции
    MoveStatus get_move_status(const Board&, const State&, Move move);
    GameStatus get_game_status(const Board&, const State&);
}