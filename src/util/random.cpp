#include "nevil/util/random.hpp"

int nevil::random::random_int(int max)
{
  return int(std::rand() % max);
}

int nevil::random::random_int(int lower_bound, int upper_bound)
{
  assert((lower_bound <= upper_bound) 
    && "ERROR: wrong values passed to the random generator");
  return std::rand()%(upper_bound + 1 - lower_bound) + lower_bound;
}

double nevil::random::random_double()
{
  return ((double)std::rand()) / RAND_MAX;
}
