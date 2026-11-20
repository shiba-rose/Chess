#ifndef RESIZABLE_WINDOW_GUARD
#define RESIZABLE_WINDOW_GUARD 1

#include <string>

#include "Window.h"

namespace Graph_lib {

class Resizable_window : public Window
{
public:
  Resizable_window(Point xy, int w, int h, const std::string& title, int min_w = 100, int min_h = 100);

  int x_max () const { return Fl_Window::w(); }
  int y_max () const { return Fl_Window::h(); }

  void set_label (const std::string& s) { copy_label(s.c_str()); }

  using Window::resize;  

  void resize (int x, int y, int w, int h) override;
  int handle (int event) override;

protected:
  virtual void on_resize (int w, int h) {}

  virtual void on_click (Point p, int button) {}
};

}  

#endif  