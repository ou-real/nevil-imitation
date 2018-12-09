#include "nevil/actor_observer_population.hpp"

nevil::actor_observer_population::actor_observer_population() {}

nevil::actor_observer_population::actor_observer_population(size_t pop_size, bool actor_observer_neuron, float bracket_ratio, float mutation_rate)
  : _population_size(pop_size)
  , _bracket_size(size_t(bracket_ratio * pop_size))
  , _mutation_rate(mutation_rate)
{
  int genome_size = 38 + 4*actor_observer_neuron;
  _individual_list = std::vector<nevil::actor_observer_individual *>(_population_size * 2);
  for (int i = 0; i < _population_size; ++i){
    _individual_list[i] = new nevil::actor_observer_individual(genome_size, true);
    _individual_list[i]->set_id(i);
    _individual_list[i + _population_size] = new nevil::actor_observer_individual(genome_size, false);
    _individual_list[i + _population_size]->set_id(i + _population_size);
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
  // Selecting (Select actors NOT observers)
  auto selected_actor_indices = nevil::evolution::tournament_selection(_individual_list.begin(), (_individual_list.begin() + _population_size - 1), _population_size, _bracket_size);

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

    new_actor_individuals[i] = _individual_list[selected_actor_indices[i]]->clone(true);
    new_actor_individuals[i]->set_id(i);

    // Copy the existing observers as is (trained through delta rule).
    new_observer_individuals[i] = _individual_list[i + _population_size]->clone(false);
    new_actor_individuals[i]->set_id(i);

    // Mutate only the actors
    new_actor_individuals[i]->mutate(_mutation_rate);
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
  for(auto a : new_observer_individuals){
    std::cout << "Observer Chromosome: ";
    for(auto i : a->get_chromosome()){
      std::cout << i << ", ";
    }
    std::cout << std::endl;
    _individual_list.push_back(a);
  }

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
