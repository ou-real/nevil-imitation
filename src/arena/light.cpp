#include "nevil/arena/light.hpp"

const Enki::Color nevil::light::DEFAULT_OFF_COLOR = Enki::Color(0.5, 0.5, 0.0);
const Enki::Color nevil::light::DEFAULT_ON_COLOR = Enki::Color(1.0, 1.0, 0.0);

nevil::light::light()
  : nevil::object()
{}

nevil::light::light(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &off_color, const Enki::Color &on_color)
  : nevil::object(x, y, size_x, size_y, height, off_color, on_color)
{}
