#include "nevil/test_arena.hpp"

nevil::test_arena::test_arena()
  : nevil::arena()
{}

nevil::test_arena::test_arena(int size_x, int size_y)
 : nevil::arena(size_x, size_y)
{
  // TODO: Setup your arena with objects
  const double OBJECT_SIZE_X = 6;
  const double OBJECT_SIZE_Y = 0.1;
  const double OBJECT_HEIGHT = 7;
  const double INITIAL_DEGREE = 0;

  //switch A
  _add_object(new nevil::switch_object(size_x / 2.0
    , size_y
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT));

    //light A
  _add_object(new nevil::light(size_x / 2.0
    , 0
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT));
  
  //--robots--
  // Create a robot named MyRobot with 0 degree angle
  _add_robot(new nevil::test_robot(size_x / 2.0
    , size_y / 2.0
    , INITIAL_DEGREE
    , "TestRobot"
    , Enki::Color(0.5, 0.0, 0.0)));
}

void nevil::test_arena::set_individuals(nevil::test_individual *i)
{
  _robot_vector[0]->set_individual(i);
}

bool nevil::test_arena::update()
{
  //  Calling the base update method
  nevil::arena::update();
  // Updating the environment
  for (auto r : _robot_vector)
  {
    // Turning the switches and lights on based on the position of the robots
    if(r->is_at_switch())
    {
      // Turn on everything
      for (auto o : _object_vector)
        o->turn_on();
    }
  }

  // Updating the robots
  for (auto r : _robot_vector)
    r->update(_object_vector);

  return true;
}
