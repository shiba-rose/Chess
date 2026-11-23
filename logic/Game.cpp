
#include <vector>
#include <cassert>
#include <algorithm>

#include "Game.h"
#include "types.h"

/* assert - программа вылетает если нарушено соглашение */

Game::Game(const Board& board, const State& state)
{
    board_ = board;
    state_ = state;
}

const Board& Game::board() const 
{
    return board_;
}

const State& Game::state() const 
{
    return state_;
}

const History& Game::history() const
{
    return history_;
}

void Game::set_history(const std::vector<Move> history)
{
    history_.set_history(history);
}

MoveResult Game::try_move(
    Coord from, Coord to, 
    FigureType promotion
)
{
    // проверка выхода за границы
    assert(Board::is_inside(from) && Board::is_inside(to)); 
    // превращение в невозможную фигуру
    assert(promotion != FigureType::King && promotion != FigureType::Pawn);
    // игра уже окончена
    assert(state_.status == GameStatus::InProgress);
    // проверка наличия фиугры
    assert(!board_.at(from).is_empty());
    // Проверка на то что превращается именно пешка
    assert((promotion != FigureType::None) ? board_.at(from).figure.type == FigureType::Pawn : 1);
    // Проверка можеть ли эта пешка превратиться по позиции ( стоит на пред последнем ряду )
    assert((promotion != FigureType::None) ? ((state_.current_move == Color::White) ? to.row == 0 : to.row == 7 ) : 1);

    std::vector<Coord> legal_moves = legal_moves_from(from);

    auto it = std::find(legal_moves.begin(), legal_moves.end(), to);

    if (it == legal_moves.end())
    {
        return MoveResult {Outcome::Impossible};
    } 

    std::vector<Coord> changed_cells {from, to};

    Figure added_figure = board_.at(from).figure;

    if (promotion != FigureType::None)
    {
        added_figure = Figure {promotion, state_.current_move};
    } else if (
        board_.at(from).figure.type == FigureType::Pawn &&
        (to.row == ((state_.current_move == Color::Black) * 7))
    )
    {
        return MoveResult {Outcome::NeedPromotion};
    }

    if (!board_.at(to).is_empty())
    {
        state_.captured_figures.push_back(board_.at(to).figure);
    }

    board_.delete_figure(from);
    board_.add_figure(to, added_figure);
    
    state_.current_move = (state_.current_move == Color::White) ? Color::Black : Color::White;
    state_.ply_count += 1;

    if (state_.ply_count >= 300)
    {
        state_.status = GameStatus::Draw;
        return MoveResult { Outcome::Draw, changed_cells };
    }

    return MoveResult {
            Outcome::Done, changed_cells
        };
}

std::vector<Coord> Game::legal_moves_from(Coord from) const
{
    // проверка выхода за границы
    assert(Board::is_inside(from)); 
    // проверка окончания партии
    assert(state_.status == GameStatus::InProgress);

    Cell cell = board_.at(from);
    Figure figure = cell.figure;

    // проверка наличия фигуры
    assert(!cell.is_empty());
    // проверка цвета фигры
    assert(figure.color == state_.current_move);

    Offset shift_up = Offset {-1, 0};
    Offset shift_down = Offset {1, 0};

    std::vector<Coord> prev_ans {};
    
    Coord prev_coord = from;
    while (Board::is_inside(prev_coord))
    {
        prev_coord += shift_up;
        if (
            Board::is_inside(prev_coord) &&
            (board_.at(prev_coord).is_empty() ||
             board_.at(prev_coord).figure.color != state_.current_move)
        )
        {
            prev_ans.push_back(prev_coord);
        }
    }

    prev_coord = from;
    while (Board::is_inside(prev_coord))
    {
        prev_coord += shift_down;
        if (
            Board::is_inside(prev_coord) && 
            (board_.at(prev_coord).is_empty() ||
             board_.at(prev_coord).figure.color != state_.current_move)
        )
        {
            prev_ans.push_back(prev_coord);
        }
    }
    return prev_ans;
}
