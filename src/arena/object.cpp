#include "nevil/arena/object.hpp"

nevil::object::object() {}

nevil::object::object(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &off_color, const Enki::Color &on_color)
{
  pos = Enki::Point(x, y);
  _off_color = off_color;
  _on_color = on_color;
  setRectangular(size_x, size_y, height, -1);
  turn_off();
}

nevil::object *nevil::object::clone() const
{
  return new nevil::object(*this);
}

bool nevil::object::is_on() const
{
  return _is_on;
}

void nevil::object::turn_on()
{
  setColor(_on_color);
  _is_on = true;
}

void nevil::object::turn_off()
{
  setColor(_off_color);
  _is_on = false;
}
