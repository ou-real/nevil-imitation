#include "nevil/arena/object.hpp"

nevil::object::object() {}

nevil::object::object(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &off_color, const Enki::Color &on_color)
  : _off_color(off_color)
  , _on_color(on_color)
{
  pos = Enki::Point(x, y);
  setRectangular(size_x, size_y, height, -1);
  turn_off();
}

nevil::object *nevil::object::clone() const
{
  return new nevil::object(*this);
}

const Enki::Color &nevil::object::get_off_color() const
{
  return _off_color;
}

const Enki::Color &nevil::object::get_on_color() const
{
  return _on_color;
}

void nevil::object::set_off_color(const Enki::Color &off_color)
{
  _off_color = off_color;
}

void nevil::object::set_on_color(const Enki::Color &on_color)
{
  _on_color = on_color;
}

nevil::object_state nevil::object::is_on() const
{
  return _state;
}

void nevil::object::turn_on()
{
  setColor(_on_color);
  _state = ON;
}

void nevil::object::turn_off()
{
  setColor(_off_color);
  _state = OFF;
}
