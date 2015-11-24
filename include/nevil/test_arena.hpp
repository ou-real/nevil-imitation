#ifndef _NEVIL_TEST_ARENA_HPP_
#define _NEVIL_TEST_ARENA_HPP_

#include "nevil/arena/arena.hpp"
#include "nevil/arena/light.hpp"
#include "nevil/arena/switch.hpp"
#include "nevil/arena/wall.hpp"
#include "nevil/test_individual.hpp"
#include "nevil/test_robot.hpp"

namespace nevil
{
  class test_arena : public arena
  {
  public:
    test_arena();
    test_arena(int size_x, int size_y);

    void set_individuals(nevil::test_individual *i);
    bool update();
  };
}
#endif // _NEVIL_TEST_ARENA_HPP_
