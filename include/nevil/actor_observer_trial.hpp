#ifndef _NEVIL_ACTOR_OBSERVER_TRIAL_HPP_
#define _NEVIL_ACTOR_OBSERVER_TRIAL_HPP_

#include "nevil/trial.hpp"
#include "nevil/actor_observer_arena.hpp"
#include "nevil/actor_observer_population.hpp"
#include "nevil/util/logger.hpp"
#include "util/parser.hpp"

namespace nevil
{
  class actor_observer_trial : public trial
  {
  public:
    actor_observer_trial();
    actor_observer_trial(const nevil::args &cl_args);
    
    bool reset();
    bool update();
    bool epoch();
    std::vector<nevil::actor_observer_individual> get_best_individuals() const;
    Enki::World *get_world() const;

  protected:
    size_t _population_size;
    size_t _current_index;

    std::vector<nevil::actor_observer_individual> _best_individuals;
    nevil::actor_observer_arena *_arena;
    nevil::actor_observer_population _population;
  };
}

#endif // _NEVIL_ACTOR_OBSERVER_TRIAL_HPP_
