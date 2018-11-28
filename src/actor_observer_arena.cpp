#include "nevil/actor_observer_arena.hpp"

nevil::actor_observer_arena::actor_observer_arena(int size_x, int size_y, bool actor_observer_neuron, double speed_actor, double speed_observer, double angle_actor, double angle_observer, const Enki::Color &arena_color)
  : nevil::arena(size_x, size_y)
  , _actor_observer_neuron(actor_observer_neuron)
{
  const double OBJECT_SIZE_X = 6;
  const double OBJECT_SIZE_Y = 0.1;
  const double OBJECT_HEIGHT = 7;

  // Switch A
  _add_object("Switch A", new nevil::switch_object(size_x / 4.0
    , size_y
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT));

  // Light A
  _add_object("Light A", new nevil::light(size_x / 4.0
    , 0
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT));

  
  // Robots

  // Create a robot named Actor
  _add_robot(new nevil::actor_observer_robot(size_x / 2.0
    , size_y *  (2/5.0)
    , angle_actor
    , actor_observer_neuron
    , speed_actor
    , "Actor"
    , Enki::Color(0.5, 0.0, 0.0)));

  // Create a robot named Observer
  _add_robot(new nevil::actor_observer_robot(size_x / 2.0
    , size_y *  (4/5.0)
    , angle_observer
    , actor_observer_neuron
    , speed_observer
    , "Observer"
    , Enki::Color(0.5, 0.0, 0.0)));
}

nevil::actor_observer_arena::~actor_observer_arena(){}

void nevil::actor_observer_arena::set_individuals(nevil::actor_observer_individual *actor, nevil::actor_observer_individual *observer)
{
  _robots[0]->set_individual(actor);
  _robots[1]->set_individual(observer);
}

bool nevil::actor_observer_arena::update()
{
  // Calling the base update method
  nevil::arena::update();

  // Updating the environment
  for (nevil::robot* r : _robots)
  {
    // If the robot is at OFF switch
    if(r->is_at(_objects["switch"], OFF))
    {
      // Turn on everything
      _objects["switch"]->turn_on();
      _objects["light"]->turn_on();
    }
  }

  // Updating the robots
  for (nevil::robot* r : _robots)
    r->update(_objects);

  return true;
}
