#ifndef WINDOW_GUARD
#define WINDOW_GUARD 1

#include <string>
#include <vector>

#include "Point.h"
#include "fltk.h"

namespace Graph_lib {

class Shape;  // "forward declare" Shape
class Widget;

class Window : public Fl_Window
{
public:
  using Fl_Window::resize;

  Window(int w, int h, const std::string& title);            // let the system pick the location
  Window(Point xy, int w, int h, const std::string& title);  // top left corner in xy

  virtual ~Window() = default;

  int x_max () const { return Fl_Widget::w(); }

  int y_max () const { return Fl_Widget::h(); }

  void resize (int ww, int hh)
  {
    size(ww, hh);
  }

  void resize (int x, int y, int w, int h) override
  {
    Fl_Window::resize(x, y, w, h);
    on_resize(w,h);
  }

  int handle(int event) override;

  void set_label (const std::string& s) { copy_label(s.c_str()); }

  void attach (Shape& s);
  void attach (Widget& w);

  void detach (Shape& s);   // remove s from shapes
  void detach (Widget& w);  // remove w from window (deactivate callbacks)

  void put_on_top (Shape& s);  // put p on top of other shapes

protected:
  void draw ();
  virtual void on_resize( int new_w,  int new_h) {}
  virtual void on_click( Point point, int button_number) {}

private:
  std::vector<Shape*> shapes;  // shapes attached to window

  void init ();
};

int gui_main ();  // invoke GUI library's main event loop

inline int x_max () { return Fl::w(); }  // width of screen in pixels

inline int y_max () { return Fl::h(); }  // height of screen in pixels

}  // namespace Graph_lib

#endif  // WINDOW_GUARD
