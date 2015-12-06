#include "nevil/arena/switch.hpp"

const Enki::Color nevil::switch_object::DEFAULT_OFF_COLOR = Enki::Color(0.4, 0.0, 1.0);
const Enki::Color nevil::switch_object::DEFAULT_ON_COLOR = Enki::Color(0.9, 1.0, 1.0);

nevil::switch_object::switch_object()
  : nevil::object()
{}

nevil::switch_object::switch_object(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &off_color, const Enki::Color &on_color)
  : nevil::object(x, y, size_x, size_y, height, off_color, on_color)
{}
