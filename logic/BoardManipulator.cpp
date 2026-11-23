
#include "types.h"
#include "move.h"
#include "BoardManipulator.h"

namespace 
{

void promtion(Board& board, Coord to, Figure prompt)
{
    if (!prompt.is_empty())
        board.add_figure(to, prompt);
}

void simple_move(Board& board, Coord from, Coord to, Figure figure = {})
{
    Figure moved_figure = board.at(from);

    board.delete_figure(from);
    board.add_figure(to, moved_figure);
    promtion(board, to, figure);
}

void enpassant(Board& board, Coord from, Coord to, Coord enpass)
{
    Figure moved_figure = board.at(from);
    board.delete_figure(from);
    board.add_figure(to, moved_figure);
    board.delete_figure(enpass);
}

void short_castling(Board& board, Coord from, Coord to)
{
    Figure moved_figure = board.at(from);

    simple_move(board, {from.row,7}, {from.row, 5});

    simple_move(board, from, to);
}

void long_castling(Board& board, Coord from, Coord to)
{
    Figure moved_figure = board.at(from);

    simple_move(board, {from.row, 0}, {from.row, 3});

    simple_move(board, from, to);
}

}

namespace BoardManipulator
{

void apply(Board& board, const Move& move)
{
    switch (move.kind)
    {
        case MoveKind::Turn: case MoveKind::Break: 
            simple_move(board, move.from, move.to, move.promtion);
            break;
        case MoveKind::EnPassant:
            enpassant(board, move.from, move.to, move.enpassant);
            break;
        case MoveKind::ShortCastling:
            short_castling(board, move.from, move.to);
            break;
        case MoveKind::LongCastling:
            long_castling(board, move.from, move.to);
            break;
    }
}

}

