#include "nevil/actor_observer_population.hpp"

nevil::actor_observer_population::actor_observer_population() {}

nevil::actor_observer_population::actor_observer_population(size_t pop_size, float bracket_ratio, float mutation_rate)
  : _population_size(pop_size)
  , _bracket_size(size_t(bracket_ratio * pop_size))
  , _mutation_rate(mutation_rate)
{
  _individual_list = std::vector<nevil::actor_observer_individual *>(_population_size);
  for (int i = 0; i < _population_size; ++i){
    _individual_list[i] = new nevil::actor_observer_individual(38, true);
    _individual_list[i + _population_size] = new nevil::actor_observer_individual(38, false);
  }
}

nevil::actor_observer_population::~actor_observer_population()
{
  for (auto i : _individual_list)
    delete i;
}

size_t nevil::actor_observer_population::size() const
{
  return _individual_list.size();
}

std::vector<nevil::actor_observer_individual> nevil::actor_observer_population::next_generation()
{
  std::cout << "Begin + pouplation_size: " << (*(_individual_list.begin() + _population_size))->get_uuid() << std::endl;
  std::cout << "Begin + pouplation_size + 1: " << (*(_individual_list.begin() + _population_size + 1))->get_uuid() << std::endl;
  // Selecting (Select actors and observers only from their pool)
  auto selected_actor_indices = nevil::evolution::tournament_selection(_individual_list.begin(), (_individual_list.begin() + _population_size), _population_size, _bracket_size);
  // Actors and observers split in the middle
  auto selected_observer_indices = nevil::evolution::tournament_selection((_individual_list.begin() + _population_size), _individual_list.end(), _population_size, _bracket_size);

  // List to store the new individuals
  std::vector<nevil::actor_observer_individual *> new_actor_individuals(_population_size);
  std::vector<nevil::actor_observer_individual *> new_observer_individuals(_population_size);

  // Track the best in each group
  nevil::actor_observer_individual *max_actor_individual = _individual_list[0];
  nevil::actor_observer_individual *max_observer_individual = _individual_list[_population_size];
  for (int i = 0; i < _population_size; ++i)
  {
    // Finding the max
    if ((*max_actor_individual) < (*_individual_list[i]))
      max_actor_individual = _individual_list[i];

    if ((*max_observer_individual) < (*_individual_list[i + _population_size]))
      max_observer_individual = _individual_list[i + _population_size];

    new_actor_individuals[i] = _individual_list[selected_actor_indices[i]]->clone();
    new_observer_individuals[i] = _individual_list[selected_observer_indices[i]]->clone();
    new_actor_individuals[i]->mutate(_mutation_rate);
    new_observer_individuals[i]->mutate(_mutation_rate);
  }

  // Store the best individuals
  std::vector<nevil::actor_observer_individual> best_individuals;
  best_individuals.push_back(*max_actor_individual);
  best_individuals.push_back(*max_observer_individual);

  // Deleting the old individuals
  for (auto i : _individual_list)
    delete i;

  // Move in the actors, replacing the empty list
  _individual_list = std::move(new_actor_individuals);

  // Append the new observers to the end
  std::move(std::begin(_individual_list), std::end(_individual_list), std::back_inserter(new_observer_individuals));

  // Clear out the observers from memory
  new_observer_individuals.clear();

  std::cout << "Population Size: " << _population_size << std::endl;
  std::cout << "New individual list size: " << _individual_list.size() << std::endl;
  
  return best_individuals;
}


nevil::actor_observer_population &nevil::actor_observer_population::operator=(const nevil::actor_observer_population &rhs)
{
  for (auto i : _individual_list)
    delete i;
  _population_size = rhs._population_size;
  _bracket_size = rhs._bracket_size;
  _mutation_rate = rhs._mutation_rate;
  _individual_list = std::vector<nevil::actor_observer_individual *> (rhs.size());
  for (int i = 0; i < _individual_list.size(); ++i)
    _individual_list[i] = new nevil::actor_observer_individual(*rhs._individual_list[i]);

  return (*this);
}


nevil::actor_observer_individual* nevil::actor_observer_population::operator[](int i)
{
  return _individual_list[i];
}