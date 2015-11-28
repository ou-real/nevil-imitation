#include "nevil/arena/robot.hpp"

nevil::robot::robot()
  : Enki::EPuck(EPuck::CAPABILITY_CAMERA) 
  {}

nevil::robot::robot(double x, double y, double angle
    , const std::string &name, const Enki::Color &color, size_t input_num, double max_speed)
  : Enki::EPuck(EPuck::CAPABILITY_CAMERA)
  , _initial_angle(angle * M_PI)
  , _initial_position(Enki::Point(x, y))
  , _robot_name(name)
  , _input_num(input_num)
  , _max_speed(max_speed)
{
  assert((max_speed <= 12.8) && "Warning the max speed of Epuck is 12.8.");
  assert((input_num >= 18) && "The minimum number of inputs should be 18");
  setColor(color);
  reset_position();
}

nevil::robot::robot(const nevil::robot &rhs)
  : Enki::EPuck(EPuck::CAPABILITY_CAMERA)
  , _initial_angle(rhs._initial_angle)
  , _initial_position(rhs._initial_position)
  , _robot_name(rhs._robot_name)
  , _input_num(rhs._input_num)
  , _max_speed(rhs._max_speed)
{
  reset_position();
}

nevil::robot::robot(nevil::robot &&rhs) noexcept
  : Enki::EPuck(EPuck::CAPABILITY_CAMERA)
  , _initial_angle(rhs._initial_angle)
  , _initial_position(std::move(rhs._initial_position))
  , _robot_name(std::move(rhs._robot_name))
  , _input_num(rhs._input_num)
  , _max_speed(rhs._max_speed)
{
  reset_position();
}

void nevil::robot::reset_position()
{
  leftSpeed = 0;
  rightSpeed = 0;
  pos = _initial_position;
  angle = _initial_angle;
}

/*
Color sets for switch and light
0.5 | 0.5 | 0.0 light turned off
1.0 | 1.0 | 0.0 light turned On

0.4 | 0.0 | 1.0 switch turned off
0.9 | 0.5 | 1.0 switch turned On  
*/
std::vector<double> nevil::robot::_get_camera_inputs()
{
  // Reset the counters
  std::vector<double> sensor_counter(_input_num, 0);

  // Each color has 6 groups of pixels
  for (size_t i = 0; i < 6; ++i)
  {
    // One group is 10 pixels
    for (size_t j = 0; j < 10; ++j)
    {
      double red_value = camera.image[i * 10 + j].r();
      // Switch
      if (red_value == 0.4)
        ++sensor_counter[i];
      // Light off
      if (red_value == 0.5)
        ++sensor_counter[i + 6];
      // Light on
      if (red_value == 1.0)
        ++sensor_counter[i + 12];
    }
  }

  // Adjust the sensor information
  for (size_t i = 0; i < _input_num; ++i)
    sensor_counter[i] = sensor_counter[i] > 7;

  return sensor_counter;
}

std::string nevil::robot::get_name() const
{
  return _robot_name;
}

double nevil::robot::_clamp(double val, double min, double max)
{
  if (val < min)
    return min;
  else if (val > max)
    return max;
  else
    return val;
}

void nevil::robot::_set_wheels_speed(double left, double right)
{
  leftSpeed = _clamp(left, -1 * _max_speed, _max_speed);
  rightSpeed = _clamp(right, -1 * _max_speed, _max_speed);
}

bool nevil::robot::is_at_switch() const
{
  for (int i = 0; i < 60; ++i)
    if (camera.image[i].r() != 0.4)
      return false;

  return true;
}

bool nevil::robot::is_at_light() const
{
  for (int i = 0; i < 60; ++i)
    if (camera.image[i].r() != 1.0)
      return false;

  return true;
}

nevil::robot &nevil::robot::operator=(const nevil::robot &rhs)
{
  _initial_angle = rhs._initial_angle;
  _initial_position = rhs._initial_position;
  _robot_name = rhs._robot_name;
  _input_num = rhs._input_num;
  _max_speed = rhs._max_speed;
  reset_position();
  return *this;
}

nevil::robot &nevil::robot::operator=(nevil::robot &&rhs) noexcept
{
  _initial_angle = rhs._initial_angle;
  _initial_position = std::move(rhs._initial_position);
  _robot_name = std::move(rhs._robot_name);
  _input_num = rhs._input_num;
  _max_speed = rhs._max_speed;
  reset_position();
  return *this;
}
