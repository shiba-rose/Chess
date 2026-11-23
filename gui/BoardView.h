#pragma once

#include <optional>
#include <string>

#include "Board.h"
#include "Graph.h"
#include "Point.h"
#include "Window.h"
#include "types.h"

const Graph_lib::Color light_color =
  Graph_lib::Color::rgb(240, 217, 181);

const Graph_lib::Color dark_color =
  Graph_lib::Color::rgb(181, 136, 99);

class BoardView;

class Board_squares : public Graph_lib::Shape
{
public:
  explicit Board_squares(const BoardView& view) : view_{view} {}

protected:
  void draw_lines () const override;

private:
  const BoardView& view_;
};

class Board_pieces : public Graph_lib::Shape
{
public:
  Board_pieces(const BoardView& view, const Board& board, const std::string& assets_dir);

  void set_cell_size (int cell_size);

protected:
  void draw_lines () const override;

private:
  static int index_of (Figure f);

  const BoardView& view_;
  const Board& board_;
  mutable Graph_lib::Vector_ref<Graph_lib::Image> images_;
};

class Board_labels : public Graph_lib::Shape
{
public:
  explicit Board_labels(const BoardView& view) : view_{view} {}

protected:
  void draw_lines () const override;

private:
  const BoardView& view_;
};

class BoardView
{
public:
  static constexpr int board_size = 8;

  BoardView(Graph_lib::Window& win, const Board& board, const std::string& assets_dir);

  void set_layout (Graph_lib::Point origin, int cell_size);

  Graph_lib::Point cell_origin (Coord c) const;
  std::optional<Coord> cell_at (Graph_lib::Point p) const;

  int cell_size () const { return cell_size_; }

private:
  Graph_lib::Point origin_{0, 0};
  int cell_size_{40};
  Board_squares squares_{*this};
  Board_labels labels_{*this};
  Board_pieces pieces_;
};