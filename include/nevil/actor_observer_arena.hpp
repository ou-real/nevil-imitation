#ifndef _NEVIL_ACTOR_OBSERVER_ARENA_HPP_
#define _NEVIL_ACTOR_OBSERVER_ARENA_HPP_

#include "nevil/arena/arena.hpp"
#include "nevil/arena/light.hpp"
#include "nevil/arena/switch.hpp"
#include "nevil/arena/wall.hpp"
#include "nevil/actor_observer_individual.hpp"
#include "nevil/actor_observer_robot.hpp"

namespace nevil
{
  class actor_observer_arena : public arena
  {
  public:
    actor_observer_arena(int size_x, int size_y, bool actor_observer_neuron, double speed_actor, double speed_observer, double angle_actor, double angle_observer, const Enki::Color &arena_color = Enki::Color(0.9, 0.9, 0.9));

    void set_individuals(actor_observer_individual *actor, actor_observer_individual *observer);
    bool update();
  };
}
#endif // _NEVIL_ACTOR_OBSERVER_ARENA_HPP_
