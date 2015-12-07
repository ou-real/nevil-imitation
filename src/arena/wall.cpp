#include "nevil/arena/wall.hpp"

nevil::wall::wall()
  : nevil::object()
{}

nevil::wall::wall(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &color)
  : nevil::object(x, y, size_x, size_y, height, color, color)
{}
