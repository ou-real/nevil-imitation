#include "nevil/actor_observer_robot.hpp"

nevil::actor_observer_robot::actor_observer_robot(double x, double y, double angle, bool actor_observer_neuron, double max_speed
      , const std::string &robot_name, const Enki::Color &color)
  : robot(x, y, angle, robot_name, color, max_speed)
  , _actor_observer_neuron(actor_observer_neuron)
  , _neural_network(robot_name == "Actor" ? static_cast<nevil::basic_nn*>(new nevil::basic_feedforward_nn(_actor_observer_neuron ? 21 : 19, 2)) : static_cast<nevil::basic_nn*>(new nevil::delta_rule_nn(_actor_observer_neuron ? 21 : 19, 2)))
  , _tick(0)
{}

nevil::robot *nevil::actor_observer_robot::clone() const
{
  std::cout << "clone actor_observer_robot" << std::endl;
  return new nevil::actor_observer_robot(*this);
}

void nevil::actor_observer_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<nevil::actor_observer_individual *> (i);
  _neural_network->set_weights(_individual->get_chromosome());
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

std::vector<double> nevil::actor_observer_robot::get_outputs(const std::vector<double> inputs){
  std::vector<double> outputs = _neural_network->get_outputs(inputs);
  return(outputs);
}

void nevil::actor_observer_robot::reset_tick(){
  _tick = 0;
}

void nevil::actor_observer_robot::update_tick(){
  ++_tick;
}


bool nevil::actor_observer_robot::update(const nevil::object_list &objects)
{
  if(get_name() == "Actor"){
    // Get the sensor information
    std::vector<double> inputs = get_inputs(objects);

    if (is_at_switch()){
      // Fitness for turning on the switch for the first time
      _individual->increase_fitness(1);
    }

    if (is_at_light())
    {
      // Fitness for being at the ON light
      _individual->increase_fitness(1);
    }

    // Evaluate the neural network
    auto output = _neural_network->update(inputs);


    // Map the [0.0, 1.0] range to the [min_speed, max_speed]
    output[0] = _range_to_max_speed(output[0], 0.0, 1.0);
    output[1] = _range_to_max_speed(output[1], 0.0, 1.0);
    
    // Pass the output of each NN and convert it to motor velocities
    _set_wheels_speed(output[0], output[1]);
  }else{
    std::cout << "Called update(1 arg) with observer robot, should be actor. ID: " << _individual->get_uuid() << std::endl;
  }

  return true;
}

bool nevil::actor_observer_robot::update(const nevil::object_list &objects, std::vector<double> actor_input, std::vector<double> actor_output)
{
  if(get_name() == "Observer"){

    // These don't effect the robot, they are only meant to measure performance
    if (is_at_switch()){
      // Fitness for turning on the switch for the first time
      _individual->increase_fitness(1);
    }

    if (is_at_light())
    {
      // Fitness for being at the ON light
      _individual->increase_fitness(1);
    }

    // Evaluate the neural network
    _neural_network->update(actor_input, actor_output);

    // Update the chromosome of the individual controlling this robot to make the changes persistent.
    _individual->set_chromosome(_neural_network->get_weights());

    std::vector<double> output = _neural_network->get_outputs(get_inputs(objects));
    
    // Map the [0.0, 1.0] range to the [min_speed, max_speed]
    output[0] = _range_to_max_speed(output[0], 0.0, 1.0);
    output[1] = _range_to_max_speed(output[1], 0.0, 1.0);
    
    // Pass the output of each NN and convert it to motor velocities
    _set_wheels_speed(output[0], output[1]);
  }else{
    std::cout << "Called update(3 arg) with actor robot, should be observer. ID: " << _individual->get_uuid() << std::endl;
  }
  
  return true;
}