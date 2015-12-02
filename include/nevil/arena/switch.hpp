#ifndef _NEVIL_ARENA_SWITCH_HPP_
#define _NEVIL_ARENA_SWITCH_HPP_

#include "nevil/arena/object.hpp"

namespace nevil
{
  class switch_object : public object
  {
   public:
    switch_object();
    switch_object(int x, int y, double size_x = 6
      , double size_y = 0.1, double height = 7
      , const Enki::Color &off_color = DEFAULT_OFF_COLOR
      , const Enki::Color &on_color = DEFAULT_ON_COLOR);

    static const Enki::Color DEFAULT_ON_COLOR;
    static const Enki::Color DEFAULT_OFF_COLOR;
  };
}

#endif  // _NEVIL_ARENA_SWITCH_HPP_
