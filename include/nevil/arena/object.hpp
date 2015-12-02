#ifndef _NEVIL_ARENA_OBJECT_HPP_
#define _NEVIL_ARENA_OBJECT_HPP_

#include <enki/PhysicalEngine.h>

namespace nevil
{
  enum object_state
  {
    ON = true,
    OFF = false
  };

  class object : public Enki::PhysicalObject
  {
   public:
    object();
    object(int x, int y, double size_x, double size_y, double height
      , const Enki::Color &off_color, const Enki::Color &on_color);

    virtual nevil::object *clone() const;
    virtual void turn_on();
    virtual void turn_off();
    nevil::object_state is_on() const;
    const Enki::Color &get_off_color() const;
    const Enki::Color &get_on_color() const;
    void set_off_color(const Enki::Color &off_color);
    void set_on_color(const Enki::Color &on_color);

   protected:
    nevil::object_state _state;
    Enki::Color _off_color;
    Enki::Color _on_color;
  };
}

#endif  // _NEVIL_ARENA_OBJECT_HPP_
