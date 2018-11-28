#ifndef _NEVIL_ACTOR_OBSERVER_POPULATION_HPP_
#define _NEVIL_ACTOR_OBSERVER_POPULATION_HPP_

#include <algorithm>
#include <iostream>
#include <vector>
#include "nevil/actor_observer_individual.hpp"
#include "nevil/util/evolution.hpp"

namespace nevil
{
  class actor_observer_population
  {
  public:
    actor_observer_population();
    actor_observer_population(size_t pop_size, bool actor_observer_neuron, float bracket_ratio, float mutation_rate);
    virtual ~actor_observer_population();

    size_t size() const;

    // Creates new generations for the actors and observers, returns a list of size 2 with the best actor then best observer.
    std::vector<nevil::actor_observer_individual> next_generation();

    actor_observer_population &operator=(const actor_observer_population &rhs);
    actor_observer_individual *operator[](int i);

  protected:
    size_t _population_size;
    size_t _bracket_size;
    float _mutation_rate;
    std::vector <nevil::actor_observer_individual *> _individual_list;
  };
}

#endif // _NEVIL_ACTOR_OBSERVER_POPULATION_HPP_