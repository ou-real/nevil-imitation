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
  for (auto r : rhs._robots)
    _add_robot(r->clone());

  for (auto o : rhs._objects)
    _add_object(o.first, o.second->clone());
}

nevil::arena::arena(nevil::arena &&rhs) noexcept
  : _world(std::move(rhs._world))
  , _robots(std::move(rhs._robots))
  , _objects(std::move(rhs._objects))
{}

nevil::arena::~arena()
{
  for (auto r : _robots)
    delete r;

  for (auto o : _objects)
    delete o.second;
}

bool nevil::arena::reset()
{
  for (auto r : _robots)
    r->reset_position();

  for (auto o : _objects)
    o.second->turn_off();
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
  _robots.push_back(r);
  _world->addObject(r);
}

void nevil::arena::_add_object(const std::string &name, nevil::object *o)
{
  _objects[name] = o;
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
  std::swap(_world, rhs._world);
  _robots = std::move(rhs._robots);
  _objects = std::move(rhs._objects);
  return *this;
}
