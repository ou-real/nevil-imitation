#include "nevil/actor_observer_robot.hpp"

nevil::actor_observer_robot::actor_observer_robot(){}

nevil::actor_observer_robot::actor_observer_robot(double x, double y, double angle, bool actor_observer_neuron, double max_speed
      , const std::string &robot_name, const Enki::Color &color)
  : robot(x, y, angle, robot_name, color, max_speed)
  , _actor_observer_neuron(actor_observer_neuron)
{
  _neural_network = nevil::basic_feedforward_nn(_actor_observer_neuron ? 21 : 19, 2);
}

nevil::robot *nevil::actor_observer_robot::clone() const
{
  std::cout << "clone actor_observer_robot" << std::endl;
  return new nevil::actor_observer_robot(*this);
}

void nevil::actor_observer_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<nevil::actor_observer_individual *> (i);
  _neural_network.set_weights(_individual->get_chromosome());
}

std::vector<double> nevil::actor_observer_robot::get_inputs(const nevil::object_list &objects){
  // Get the sensor information
  std::vector<double> inputs = _get_camera_inputs(objects);

  // If it is an actor
  if(_individual->is_actor())
  {
    // Add the actor inputs, if using 'unique neurons'
    if(_actor_observer_neuron)
    {
      inputs.push_back(1);
      inputs.push_back(0);
    }
  }
  // If it is a observer
  else {
    // Add the observer inputs, if using 'unique neurons'
    if(_actor_observer_neuron)
    {
      inputs.push_back(0);
      inputs.push_back(1);
    }
  }

  // Add the bias input
  inputs.push_back(1);

  return inputs;
}

bool nevil::actor_observer_robot::update(const nevil::object_list &objects)
{
  // Get the sensor information
  std::vector<double> inputs = get_inputs(objects);

  if (is_at_switch()){

  }

  if (is_at_light())
  {
    _individual->increase_fitness(1);
  }

  // Evaluate the neural network
  auto output = _neural_network.update(inputs);

  // Pass the output of each NN and convert it to motor velocities
  _set_wheels_speed(output[0], output[1]);

  return true;
}