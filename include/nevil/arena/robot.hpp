#ifndef _NEVIL_ARENA_ROBOT_HPP_
#define _NEVIL_ARENA_ROBOT_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <enki/robots/e-puck/EPuck.h>
#include "nevil/individual.hpp"
#include "nevil/arena/object.hpp"

namespace nevil
{
  class robot: public Enki::EPuck
  {
   public:
    robot();
    robot(double x, double y, double angle, const std::string &name
      , const Enki::Color &color, size_t input_num = 18, double max_speed = 12.8);
    robot(const nevil::robot &rhs);
    robot(nevil::robot &&rhs) noexcept;

    virtual nevil::robot *clone() const = 0;
    virtual bool update(const std::vector<object *> &objects) = 0;
    virtual void set_individual(nevil::individual *i) = 0;

    virtual void reset_position();
    virtual bool is_at_switch() const;
    virtual bool is_at_light() const;
    std::string get_name() const;

    nevil::robot &operator=(const nevil::robot &rhs);
    nevil::robot &operator=(nevil::robot &&rhs) noexcept;

   protected:
    void _set_wheels_speed(double left, double right);
    double _clamp(double val, double min, double max);
    virtual std::vector<double> _get_camera_inputs();

    double _initial_angle;
    Enki::Point _initial_position;
    std::string _robot_name;
    size_t _input_num;
    double _max_speed;
  };
}

#endif  // _NEVIL_ARENA_ROBOT_HPP_
