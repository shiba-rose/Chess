#include <algorithm>
#include <iostream>
#include <vector>

#include "types.h"
#include "State.h"
#include "Board.h"
#include "Game.h"

static int g_failed = 0;

#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            ++g_failed;                                                    \
            std::cout << "FAIL " << __FILE__ << ":" << __LINE__            \
                      << "  " #cond << "\n";                               \
        }                                                                  \
    } while (0)

static bool is_fig(Figure f, FigureType t, Color c)
{
    return f.type == t && f.color == c;
}

static bool contains(const std::vector<Coord>& v, Coord c)
{
    return std::find(v.begin(), v.end(), c) != v.end();
}

// Пустая доска с двумя королями в углах, чтобы позиция была "настоящей"
static Board board_with_kings()
{
    Board b;
    b.clear();
    b.add_figure({7, 0}, {FigureType::King, Color::White});
    b.add_figure({0, 7}, {FigureType::King, Color::Black});
    return b;
}

static void test_initial_position()
{
    Game g;
    CHECK(is_fig(g.board().at({7, 4}), FigureType::King,  Color::White));
    CHECK(is_fig(g.board().at({7, 3}), FigureType::Queen, Color::White));
    CHECK(is_fig(g.board().at({0, 4}), FigureType::King,  Color::Black));
    CHECK(is_fig(g.board().at({0, 3}), FigureType::Queen, Color::Black));
    CHECK(is_fig(g.board().at({6, 0}), FigureType::Pawn,  Color::White));
    CHECK(is_fig(g.board().at({1, 0}), FigureType::Pawn,  Color::Black));
    CHECK(g.board().at({4, 4}).is_empty());

    int count = 0;
    for (const Figure& f : g.board().cells())
        if (!f.is_empty()) ++count;
    CHECK(count == 32);

    CHECK(g.state().current_move == Color::White);
    CHECK(g.state().status == GameStatus::InProgress);
    CHECK(g.state().ply_count == 0);
    CHECK(g.state().captured_figures.empty());
}

static void test_legal_moves()
{
    Game g;
    std::vector<Coord> m = g.legal_moves_from({6, 4});   // белая пешка e2

    // вверх: 4 пустые клетки + две чужие фигуры; вниз: своя, не берём
    CHECK(m.size() == 6);
    CHECK(contains(m, {5, 4}));
    CHECK(contains(m, {4, 4}));
    CHECK(contains(m, {1, 4}));     // чужая фигура: можно взять
    CHECK(!contains(m, {7, 4}));    // своя фигура: нельзя
    CHECK(!contains(m, {6, 4}));    // сама клетка
    CHECK(!contains(m, {6, 5}));    // по горизонтали заглушка не ходит
}

static void test_simple_moves_and_turn()
{
    Game g;

    MoveResult r1 = g.try_move({6, 4}, {4, 4});
    CHECK(r1.outcome == Outcome::Done);
    CHECK(r1.changed_cells.size() == 2);
    CHECK(contains(r1.changed_cells, {6, 4}));
    CHECK(contains(r1.changed_cells, {4, 4}));
    CHECK(g.board().at({6, 4}).is_empty());
    CHECK(is_fig(g.board().at({4, 4}), FigureType::Pawn, Color::White));
    CHECK(g.state().current_move == Color::Black);
    CHECK(g.state().ply_count == 1);

    MoveResult r2 = g.try_move({1, 3}, {3, 3});          // чёрная пешка d7
    CHECK(r2.outcome == Outcome::Done);
    CHECK(is_fig(g.board().at({3, 3}), FigureType::Pawn, Color::Black));
    CHECK(g.state().current_move == Color::White);
    CHECK(g.state().ply_count == 2);
}

static void test_impossible_changes_nothing()
{
    Game g;
    MoveResult r = g.try_move({6, 4}, {6, 5});           // вбок: нет в списке ходов
    CHECK(r.outcome == Outcome::Impossible);
    CHECK(r.changed_cells.empty());
    CHECK(is_fig(g.board().at({6, 4}), FigureType::Pawn, Color::White));
    CHECK(g.board().at({6, 5}).type == FigureType::Pawn);   // соседняя пешка на месте
    CHECK(g.state().current_move == Color::White);
    CHECK(g.state().ply_count == 0);
}

static void test_capture()
{
    Board b = board_with_kings();
    b.add_figure({4, 4}, {FigureType::Rook,   Color::White});
    b.add_figure({2, 4}, {FigureType::Knight, Color::Black});
    Game g(b, State{});

    MoveResult r = g.try_move({4, 4}, {2, 4});
    CHECK(r.outcome == Outcome::Done);
    CHECK(is_fig(g.board().at({2, 4}), FigureType::Rook, Color::White));
    CHECK(g.board().at({4, 4}).is_empty());
    CHECK(g.state().captured_figures.size() == 1);
    CHECK(is_fig(g.state().captured_figures[0], FigureType::Knight, Color::Black));
}

static void test_promotion_white()
{
    Board b = board_with_kings();
    b.add_figure({1, 4}, {FigureType::Pawn, Color::White});

    // без выбора фигуры: ничего не меняется
    Game g(b, State{});
    MoveResult r1 = g.try_move({1, 4}, {0, 4});
    CHECK(r1.outcome == Outcome::NeedPromotion);
    CHECK(r1.changed_cells.empty());
    CHECK(is_fig(g.board().at({1, 4}), FigureType::Pawn, Color::White));
    CHECK(g.board().at({0, 4}).is_empty());
    CHECK(g.state().current_move == Color::White);
    CHECK(g.state().ply_count == 0);

    // повтор с фигурой
    MoveResult r2 = g.try_move({1, 4}, {0, 4}, FigureType::Queen);
    CHECK(r2.outcome == Outcome::Done);
    CHECK(is_fig(g.board().at({0, 4}), FigureType::Queen, Color::White));
    CHECK(g.board().at({1, 4}).is_empty());
    CHECK(g.state().current_move == Color::Black);
}

static void test_promotion_black()
{
    Board b = board_with_kings();
    b.add_figure({6, 4}, {FigureType::Pawn, Color::Black});
    State s;
    s.current_move = Color::Black;
    Game g(b, s);

    MoveResult r1 = g.try_move({6, 4}, {7, 4});
    CHECK(r1.outcome == Outcome::NeedPromotion);

    MoveResult r2 = g.try_move({6, 4}, {7, 4}, FigureType::Knight);
    CHECK(r2.outcome == Outcome::Done);
    CHECK(is_fig(g.board().at({7, 4}), FigureType::Knight, Color::Black));
    CHECK(g.state().current_move == Color::White);
}

static void test_draw_by_ply_limit()
{
    Board b = board_with_kings();
    b.add_figure({4, 4}, {FigureType::Rook, Color::White});
    State s;
    s.ply_count = 299;
    Game g(b, s);

    MoveResult r = g.try_move({4, 4}, {3, 4});
    CHECK(r.outcome == Outcome::Draw);
    CHECK(r.changed_cells.size() == 2);                  // ход применён
    CHECK(is_fig(g.board().at({3, 4}), FigureType::Rook, Color::White));
    CHECK(g.state().status == GameStatus::Draw);
    CHECK(g.state().ply_count == 300);
}

int main()
{
    test_initial_position();
    test_legal_moves();
    test_simple_moves_and_turn();
    test_impossible_changes_nothing();
    test_capture();
    test_promotion_white();
    test_promotion_black();
    test_draw_by_ply_limit();

    if (g_failed == 0)
        std::cout << "ALL OK\n";
    else
        std::cout << g_failed << " check(s) failed\n";
    return g_failed == 0 ? 0 : 1;
}