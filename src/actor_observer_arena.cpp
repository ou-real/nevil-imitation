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
    , size_y / 2.0
    , angle_actor
    , actor_observer_neuron
    , speed_actor
    , "Actor"
    , Enki::Color(0.5, 0.0, 0.0)));

  // Create a robot named Observer
  _add_robot(new nevil::actor_observer_robot(size_x
    , size_y *  (4/5.0)
    , angle_observer
    , actor_observer_neuron
    , speed_observer
    , "Observer"
    , Enki::Color(0.0, 0.6, 0.0)));
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

    // If key not found in map iterator to end is returned 
    if (_objects.find("Switch A") == _objects.end()) 
        std::cout << "Switch A" << " not found\n\n"; 

    // If the robot is at OFF switch
    if(r->is_at_switch())
    {
      
      // Turn on everything
      _objects["Switch A"]->turn_on();
      _objects["Light A"]->turn_on();
    }
  }

  // Updating the robots
  // Assumes n-actors, then n-observers
  int num_robots = _robots.size();
  assert(num_robots % 2 == 0 && "The number of robots must be even (1 observer per actor)");

  for(int i = 0; i < num_robots / 2; ++i){
    actor_observer_robot* actor_robot = static_cast<actor_observer_robot*>(_robots[i]);
    actor_observer_robot* observer_robot = static_cast<actor_observer_robot*>(_robots[i+num_robots/2]);


    std::vector<double> actor_inputs = actor_robot->get_inputs(_objects);
    std::vector<double> actor_outputs = actor_robot->get_outputs(actor_inputs);

    // Pass the actors view into the observer
    std::vector<double> observer_outputs = observer_robot->get_outputs(actor_inputs);
  }

  for (nevil::robot* r : _robots){
    if(r->get_name() == "Actor"){
      
      r->update(_objects);
    }
  }

  return true;
}
