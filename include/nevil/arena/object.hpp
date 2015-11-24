#ifndef _NEVIL_ARENA_OBJECT_HPP_
#define _NEVIL_ARENA_OBJECT_HPP_

#include <enki/PhysicalEngine.h>

namespace nevil
{
  class object : public Enki::PhysicalObject
  {
   public:
    object();
    object(int x, int y, double size_x, double size_y, double height
      , const Enki::Color &off_color, const Enki::Color &on_color);

    virtual nevil::object *clone() const;
    virtual void turn_on();
    virtual void turn_off();
    bool is_on() const;

   protected:
    bool _is_on;
    Enki::Color _on_color;
    Enki::Color _off_color;
  };
}

#endif  // _NEVIL_ARENA_OBJECT_HPP_
