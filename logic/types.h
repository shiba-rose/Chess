#pragma once

#include <vector>

struct Coord { int row, col; };                // (0,0) = a8 (левый верхний угол), row уменьшается к чёрным
struct Offset { int drow, dcol; };

inline Coord operator+(Coord a, Offset b) 
{ 
    return Coord{a.row + b.drow, a.col + b.dcol}; 
}

inline Coord& operator+=(Coord& a, Offset b) 
{
    a.row += b.drow;
    a.col += b.dcol;
    return a;
}

inline Offset operator-(Coord a, Coord b) 
{ 
    return Offset{a.row - b.row, a.col - b.col}; 
}

inline bool operator==(const Coord& a, const Coord& b)
{
    return (a.row == b.row) && (a.col == b.col);
}

enum class Color      { White, Black };
enum class FigureType { None, Pawn, Knight, Bishop, Rook, Queen, King };

struct Figure {
    FigureType type  = FigureType::None;
    Color      color = Color::White;           // при None игнорируется
};

enum class GameStatus { InProgress, Checkmate, Stalemate, Draw };

enum class Outcome {
    // ход ПРИМЕНЁН: доска изменилась, changed_cells заполнен
    Done, Check, Checkmate, Stalemate, Draw,
    // ход НЕ применён: доска не менялась, changed_cells пуст
    NeedPromotion, Impossible
};

struct MoveResult {
    Outcome            outcome;
    std::vector<Coord> changed_cells {};
    Coord              check_cell {0, 0};           // осмыслен только при Check: клетка короля под шахом
};