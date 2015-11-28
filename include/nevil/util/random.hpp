#ifndef _NEVIL_UTIL_RANDOM_HPP_
#define _NEVIL_UTIL_RANDOM_HPP_

#include <cstdlib>
#include <cassert>
#include <climits>

namespace nevil
{
  namespace random
  {
    // Returns a random integer
    int random_int(int max = INT_MAX);
    // Returns an integer in range [lower_bound, upper_bound] (inclusive)
    int random_int(int lower_bound, int upper_bound);
    // Returns a random double between [0 and 1]
    double random_double();
  }
}

#endif // _NEVIL_UTIL_RANDOM_HPP_
