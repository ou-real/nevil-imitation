#include "nevil/arena/arena.hpp"

nevil::arena::arena() 
{
  _world.reset(new Enki::World());
  _world->takeObjectOwnership(false);
}

nevil::arena::arena(int size_x, int size_y, const Enki::Color &color)
{
  _world.reset(new Enki::World(size_x, size_y, color));
  _world->takeObjectOwnership(false);
}

nevil::arena::arena(const nevil::arena &rhs)
{
  _world.reset(new Enki::World(rhs._world->w, rhs._world->h, rhs._world->wallsColor));
  _world->takeObjectOwnership(false);
  for (auto r : rhs._robot_vector)
    _add_robot(r->clone());

  for (auto o : rhs._object_vector)
    _add_object(o->clone());
}

nevil::arena::arena(nevil::arena &&rhs) noexcept
  : _world(std::move(rhs._world))
  , _robot_vector(std::move(rhs._robot_vector))
  , _object_vector(std::move(rhs._object_vector))
{}

nevil::arena::~arena()
{
  for (auto r : _robot_vector)
    delete r;

  for (auto o : _object_vector)
    delete o;
}

bool nevil::arena::reset()
{
  for (auto r : _robot_vector)
    r->reset_position();

  for (auto o : _object_vector)
    o->turn_off();
  return true;
}

Enki::World *nevil::arena::get_world() const
{
  return _world.get();
}

bool nevil::arena::update()
{
  // step of 50 ms
  _world->step(1.0/30, 1);
  return true;
}

void nevil::arena::_add_robot(nevil::robot *r)
{
  _robot_vector.push_back(r);
  _world->addObject(r);
}

void nevil::arena::_add_object(nevil::object *o)
{
  _object_vector.push_back(o);
  _world->addObject(o);
}

nevil::arena &nevil::arena::operator=(const nevil::arena &rhs)
{
  nevil::arena tmp(rhs);
  *this = std::move(tmp);
  return *this;
}

nevil::arena &nevil::arena::operator=(nevil::arena &&rhs) noexcept
{
  std::cout << "move arena" << std::endl;
  std::swap(_world, rhs._world);
  _robot_vector = std::move(rhs._robot_vector);
  _object_vector = std::move(rhs._object_vector);
  return *this;
}
