#ifndef _NEVIL_TRIAL_HPP_
#define _NEVIL_TRIAL_HPP_

#include "nevil/arena/arena.hpp"
#include "nevil/individual.hpp"

namespace nevil
{
  class trial
  {
  public:
    virtual bool reset() = 0;
    virtual bool update() = 0;
    virtual bool epoch() = 0;
    virtual Enki::World *get_world() const = 0;
  };
}

#endif // _NEVIL_TRIAL_HPP_
