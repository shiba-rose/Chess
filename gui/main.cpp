#include <iostream>
#include "GUI.h"
#include "BoardView.h"
#include "GameWindow.h"

/*struct Test_window : Graph_lib::Resizable_window
{
  Test_window(Graph_lib::Point xy, int w, int h, const std::string& title)
      : Graph_lib::Resizable_window{xy, w, h, title, 400, 400},
        btn{Graph_lib::Point{w - 70, 0}, 70, 20, "Btn", cb_btn}
       {
        attach(btn);
       }
  
protected:
  void on_resize (int w, int h) override
  {
    std::cout << "размер: " << w << " x " << h << '\n';
  }

  void on_click (Graph_lib::Point p, int button) override
  {
  std::cout << "клик: (" << p.x << ", " << p.y << "), кнопка " << button << '\n';
  }
private:
  Graph_lib::Button btn;

  static void cb_btn (Graph_lib::Address, Graph_lib::Address)
  {
    std::cout << "кнопка нажата\n";
  }
};*/

int main()
{
  /*using namespace Graph_lib;
  Test_window win{Graph_lib::Point{100, 100}, 600, 400, "test"};
  const int cell_size = 80;

    Rectangle light_sq{Point{60, 60}, cell_size, cell_size};
    light_sq.set_fill_color(Color::rgb(240, 217, 181));

    Rectangle dark_sq{Point{60 + cell_size, 60}, cell_size, cell_size};
    dark_sq.set_fill_color(Color::rgb(181, 136, 99));

    Graph_lib::Image king{Graph_lib::Point{220, 220}, "C:/project/Chess/assets/wK.svg"};
    king.set_size(100, 100);
    win.attach(king);

    win.attach(light_sq);
    win.attach(dark_sq);*/

    /*Graph_lib::Window win{800, 600, "Chess"};
    BoardView view{win};
    view.set_layout(Graph_lib::Point{20, 20}, 50);*/

    GameWindow win{Graph_lib::Point{100, 100}, 1000, 700, "Chess"};
  return Graph_lib::gui_main();
}