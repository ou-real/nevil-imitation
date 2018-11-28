#include "nevil/actor_observer_trial.hpp"

nevil::actor_observer_trial::actor_observer_trial() {}

nevil::actor_observer_trial::actor_observer_trial(const nevil::args &cl_args)
{
  const int WORLD_SIZE_X = 40;
  const int WORLD_SIZE_Y = 50;

  nevil::args local_args(cl_args);
  _population_size = std::stoi(local_args["ps"]);
  bool actor_observer_neuron = (local_args["sn"] == "true");
  double bracket_ratio = std::stod(local_args["br"]);
  double mutation_rate = std::stod(local_args["mr"]);
  double speed_A = std::stod(local_args["speedA"]);
  double speed_O = std::stod(local_args["speedO"]);
  double angle_A = std::stod(local_args["angleA"]);
  double angle_O = std::stod(local_args["speedO"]);

  _arena = new nevil::actor_observer_arena(WORLD_SIZE_X, WORLD_SIZE_Y, actor_observer_neuron, speed_A, speed_O, angle_A, angle_O);
  _population = nevil::actor_observer_population(_population_size, actor_observer_neuron, bracket_ratio, mutation_rate);
  _current_index = 0;
}

Enki::World *nevil::actor_observer_trial::get_world() const
{
  return _arena->get_world();
}

bool nevil::actor_observer_trial::update()
{
  return _arena->update();
}

bool nevil::actor_observer_trial::reset()
{
  _arena->set_individuals(_population[_current_index], _population[_current_index + _population_size]);
  ++_current_index;
  return _arena->reset();
}

bool nevil::actor_observer_trial::epoch()
{
  _best_individuals = _population.next_generation();
  _current_index = 0;
  return true;
}

std::vector<nevil::actor_observer_individual> nevil::actor_observer_trial::get_best_individuals() const
{
  return _best_individuals;
}
