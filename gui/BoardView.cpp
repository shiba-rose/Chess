#include "BoardView.h"


void BoardView::set_layout(Graph_lib::Point origin, int cell_size)
{
    origin_ = origin;
    cell_size_ = cell_size;
    pieces_.set_cell_size(cell_size);
}



Graph_lib::Point BoardView::cell_origin(Coord c) const
{
    int x {origin_.x + c.col * cell_size_};
    int y {origin_.y + c.row * cell_size_};
    return Graph_lib::Point(x,y);
}

std::optional<Coord> BoardView::cell_at(Graph_lib::Point p) const
{
    int dx = p.x - origin_.x;
    int dy = p.y - origin_.y;

    if (dx < 0 || dy < 0 ||
        dx >= board_size * cell_size_ ||
        dy >= board_size * cell_size_)
        return std::nullopt;

    int col = dx / cell_size_;
    int row = dy / cell_size_;

    return Coord{row, col};
}

BoardView::BoardView(
    Graph_lib::Window& win,
    const Board& board,
    const std::string& assets_dir
)
    : pieces_{*this, board, assets_dir}
{
    win.attach(squares_);
    win.attach(pieces_); 
    win.attach(labels_);
}

void Board_squares::draw_lines() const
{
    for (int row = 0; row < 8; ++row)
{
        for (int col = 0; col < 8; ++col)
        {
            if ((row + col) % 2 == 0)
                fl_color(light_color.as_int());

            else
                fl_color(dark_color.as_int());

            auto p = view_.cell_origin(Coord{row, col});

            fl_rectf(p.x, p.y,
                view_.cell_size(),
                view_.cell_size());
        }
    }
}

Board_pieces::Board_pieces(
    const BoardView& view,
    const Board& board,
    const std::string& assets_dir
)
    : view_{view}, board_{board}
{
    const char* colors[] = {"w", "b"};
    const char* figures[] = {"P", "N", "B", "R", "Q", "K"};

    for (const char* color : colors) {
        for (const char* figure : figures) {
            std::string path = assets_dir + "/" + color + figure + ".svg";

            images_.push_back(
                new Graph_lib::Image{Graph_lib::Point{0, 0}, path}
            );
        }
    }
}


void Board_pieces::set_cell_size(int cell_size)
{
    for (int i = 0; i < 12; ++i)
        images_[i].set_size(cell_size, cell_size);
}


int Board_pieces::index_of(Figure f)
{
    if (f.is_empty()) return -1;

    int type = static_cast<int>(f.type) - 1;

    if (f.color == Color::White) return type;

    return 6 + type;
}


void Board_pieces::draw_lines() const
{
    for (int i = 0; i < 64; ++i) {
        Coord c = Board::coord_of(i);
        Figure f = board_.at(c);

        if (f.is_empty()) continue;

        int image_index = index_of(f);

        images_[image_index].set_position(view_.cell_origin(c));
        images_[image_index].draw();
    }
}

void Board_labels::draw_lines() const
{
    const int size = view_.cell_size();
    const int margin = size / 25 -2;

    fl_font(Graph_lib::Font::helvetica_bold, size / 5);

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (row != 7 && col != 0)
                continue;

            if ((row + col) % 2)
                fl_color(light_color.as_int());
            else
                fl_color(dark_color.as_int());

            Graph_lib::Point p = view_.cell_origin(Coord{row, col});

            if (row == 7)
            {
                char letter = 'a' + col;
                std::string text {letter};

                int x = p.x + size - margin
                    - static_cast<int>(fl_width(text.c_str()));
                int y = p.y + size - margin - fl_descent();

                fl_draw(text.c_str(), x, y);
            }

            if (col == 0)
            {
                std::string text = std::to_string(8 - row);

                int x = p.x + margin;
                int y = p.y + margin + fl_height() - fl_descent();

                fl_draw(text.c_str(), x, y);
            }
        }
    }
}