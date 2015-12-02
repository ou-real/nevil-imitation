#include "nevil/test_arena.hpp"

nevil::test_arena::test_arena()
  : nevil::arena()
{}

nevil::test_arena::test_arena(int size_x, int size_y)
  : nevil::arena(size_x, size_y)
{
  // TODO: Setup your arena with objects
  //  switch
  _add_object("switch", new nevil::switch_object(size_x / 2.0, size_y));
  //  light
  _add_object("light", new nevil::light(size_x / 2.0, 0));
  
  //--robots--
  // Create a robot named TestRobot with 0 degree angle
  _add_robot(new nevil::test_robot(size_x / 2.0
    , size_y / 2.0
    , 0
    , "TestRobot"
    , Enki::Color(0.5, 0.0, 0.0)));
}

void nevil::test_arena::set_individuals(nevil::test_individual *i)
{
  _robots[0]->set_individual(i);
}

bool nevil::test_arena::update()
{
  // Calling the base update method
  nevil::arena::update();
  // Updating the environment
  for (auto r : _robots)
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
  for (auto r : _robots)
    r->update(_objects);

  return true;
}
