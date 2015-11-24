#include "nevil/arena/switch.hpp"

nevil::switch_object::switch_object()
  : nevil::object()
  {}

nevil::switch_object::switch_object(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &off_color, const Enki::Color &on_color)
  : nevil::object(x, y, size_x, size_y, height, off_color, on_color)
  {}
