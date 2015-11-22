#include "nevil/util/random.hpp"

int nevil::random::random_int(int lower_bound, int upper_bound)
{
  assert((lower_bound <= upper_bound) && "ERROR: wrong values passed to the random generator");

  int result = rand()%(upper_bound + 1 - lower_bound) + lower_bound;

  assert(result <= upper_bound && result >= lower_bound);
  return result;
}
