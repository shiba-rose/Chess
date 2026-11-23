
#include <vector>
#include <array>

#include "move.h"
#include "board.h"
#include "state.h"
#include "types.h"
#include "Analyzer.h"

namespace Analyzer
{
// Функции поиска хода
Move get_correct_move(const Board&, const State&, Coord c1, Coord c2)
{

}

std::vector<Coord> get_legal_moves(const Board&, const State&, Coord c1)
{

}
    
// Функции анализа позиции
MoveStatus get_move_status(const Board&, const State&, Move move)
{

}

GameStatus get_game_status(const Board&, const State&)
{

}

}

// Внутренняя реализации анализатора

namespace 
{

// Заметим что смещения белых и черных пешек отлчиаются только знаком
// Смещения фигур

std::array<Offset, 4> Pawn_Offsets = {{
    {-1, 0}, {-2, 0}, {-1, -1}, {-1, 1}
}}; // для белой пешки

std::array<Offset, 8> Knight_Offsets = {{
    {1, 2},   {2, 1},   {2, -1}, {1, -2},
    {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
}};

std::array<Offset, 28> Bishop_Offsets = {{
    {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
    {6, 6}, {7, 7}, {-1, -1}, {-2, -2}, 
    {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6},
    {-7, -7}, {1, -1}, {2, -2}, {3, -3}, 
    {4, -4}, {5, -5}, {6, -6}, {7, -7}, 
    {-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, 
    {-5, 5}, {-6, 6}, {-7, 7}
}};

std::array<Offset, 28> Root_Offsets = {{
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
    {0, 6}, {0, 7}, {0, -1}, {0, -2}, 
    {0, -3}, {0, -4}, {0, -5}, {0, -6},
    {0, -7}, {1, 0}, {2, 0}, {3, 0}, 
    {4, 0}, {5, 0}, {6, 0}, {7, 0}, 
    {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, 
    {-5, 0}, {-6, 0}, {-7, 0}
}};

std::vector<Move> get_geometry_correct_moves(Coord c, FigureType fig_type)
{

}
}