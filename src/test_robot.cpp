#include "nevil/test_robot.hpp"

nevil::test_robot::test_robot()
  : robot()
{}

nevil::test_robot::test_robot(double x, double y, double angle, 
  const std::string &robot_name, const Enki::Color &color, size_t input_num)
  : robot(x, y, angle, robot_name, color, input_num)
  , _neural_network(nevil::basic_feedforward_nn(input_num, 2))
{}

nevil::test_robot::test_robot(const nevil::test_robot &rhs)
  : nevil::robot::robot(rhs)
  , _individual(rhs._individual)
  , _neural_network(rhs._neural_network)
{
  std::cout << "copy constructor test_robot" << std::endl;
}

nevil::test_robot::test_robot(nevil::test_robot &&rhs) noexcept
  : nevil::robot::robot(std::move(rhs))
  , _individual(rhs._individual)
  , _neural_network(std::move(rhs._neural_network))
{
  std::cout << "move constructor test_robot" << std::endl;
}

nevil::robot *nevil::test_robot::clone() const
{
  return new nevil::test_robot(*this);
}

void nevil::test_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<nevil::test_individual *> (i);
  _neural_network.set_weights(_individual->get_chromosome());
}

bool nevil::test_robot::update(const std::vector<object *> &objects)
{
  // Increase robot's fitness if its under the light
  if (is_at_light())
    _individual->increase_fitness(1);
  // Get the sensor information
  std::vector<double> inputs = _get_camera_inputs();
  // Add the bias input
  inputs[_input_num - 1] = 1;
  // Evaluate the neural network
  std::vector <double> output = _neural_network.update(inputs);
  // Pass the output of each NN and convert it to motor velocities
  _set_wheels_speed(output[0], output[1]);
  return true;
}

nevil::test_robot &nevil::test_robot::operator=(const nevil::test_robot &rhs)
{
  std::cout << "= test_robot" << std::endl;
  nevil::test_robot tmp(rhs);
  *this = std::move(tmp);
  return *this;
}

nevil::test_robot &nevil::test_robot::operator=(nevil::test_robot &&rhs) noexcept
{
  std::cout << "move = test_robot" << std::endl;
  nevil::robot::operator=(std::move(rhs));
  _individual = rhs._individual;
  _neural_network = std::move(rhs._neural_network);
  return *this;
}