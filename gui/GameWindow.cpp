#include "GameWindow.h"

#include <iostream>
#include <algorithm>

GameWindow::GameWindow(
    Graph_lib::Point xy,
    int w,
    int h,
    const std::string& title
)
    : Graph_lib::Resizable_window{xy, w, h, title, 800, 600}
{
    update_layout(w, h);
}

void GameWindow::on_resize(int w, int h)
{
    update_layout(w, h);
}


void GameWindow::on_click(Graph_lib::Point p, int)
{
    auto cell = board_view_.cell_at(p);

    if (cell)
    {
        std::cout << "Row: " << cell->row
                  << ", Col: " << cell->col << '\n';
    }
}

void GameWindow::update_layout(int w, int h)
{
    int history_width = std::max(200, w / 4);

    int board_area_width = w - history_width;

    int cell_size = std::min(board_area_width, h) / BoardView::board_size;

    int board_pixels = cell_size * BoardView::board_size;


    int x = (board_area_width - board_pixels) / 2;
    int y = (h - board_pixels) / 2;

    board_view_.set_layout(
        Graph_lib::Point{x, y},
        cell_size
    );

    redraw();
}