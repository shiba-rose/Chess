#pragma once

#include <string>

#include "BoardView.h"
#include "Resizable_window.h"
#include "Board.h"

class GameWindow : public Graph_lib::Resizable_window
{
public:
  GameWindow(Graph_lib::Point xy, int w, int h, const std::string& title);

protected:
  void on_resize (int w, int h) override;
  void on_click (Graph_lib::Point p, int button) override;

private:
  void update_layout (int w, int h);
  Board board_;
  BoardView board_view_{*this, board_, "C:/project/Chess/assets"};
};