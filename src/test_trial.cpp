#include "nevil/test_trial.hpp"

nevil::test_trial::test_trial() {}

nevil::test_trial::test_trial(const nevil::args &cl_args)
{
  const int WORLD_SIZE_X = 40;
  const int WORLD_SIZE_Y = 50;

  nevil::args local_args(cl_args);
  _population_size = std::stoi(local_args["ps"]);
  double bracket_ratio = std::stod(local_args["br"]);
  double mutation_rate = std::stod(local_args["mr"]);

  _arena = nevil::test_arena(WORLD_SIZE_X, WORLD_SIZE_Y);
  _population = nevil::test_population(_population_size, bracket_ratio, mutation_rate);
  _current_index = 0;
}

Enki::World *nevil::test_trial::get_world() const
{
  return _arena.get_world();
}

bool nevil::test_trial::update()
{
  return _arena.update();
}

bool nevil::test_trial::reset()
{
  _arena.set_individuals(_population[_current_index]);
  ++_current_index;
  return _arena.reset();
}

bool nevil::test_trial::epoch()
{
  _best_individual = _population.next_generation();
  _current_index = 0;
  return true;
}

nevil::test_individual nevil::test_trial::get_best_individual() const
{
  return _best_individual;
}
