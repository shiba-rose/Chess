#include "Resizable_window.h"

namespace Graph_lib {

Resizable_window::Resizable_window(Point xy, int w, int h, const std::string& title, int min_w, int min_h)
    : Window{xy, w, h, title}
    
{
  size_range(min_w, min_h);
}

void Resizable_window::resize(int x, int y, int w, int h)
{
  Fl_Window::resize(x, y, w, h);
  on_resize(w, h);
}

int Resizable_window::handle(int event)
{
  const int base_result = Fl_Window::handle(event);
  if (base_result != 0)
    return base_result;

  if (event == FL_PUSH)
  {
    on_click(Point{Fl::event_x(), Fl::event_y()}, Fl::event_button());
    return 1;
  }

  return 0;
}

}  