#ifndef _NEVIL_UTIL_EVOLUTION_HPP_
#define _NEVIL_UTIL_EVOLUTION_HPP_

#include <cassert>
#include <vector>
#include "nevil/util/random.hpp"

namespace nevil
{
  namespace evolution
  {
    template <class RandomAccessIterator>
    inline std::vector<unsigned int> tournament_selection(const RandomAccessIterator &start
      , const RandomAccessIterator &end, std::size_t new_size, std::size_t pool_size)
    {
      std::size_t pop_size = (end - start);
      std::vector<unsigned int> bracket(pool_size);
      std::vector<unsigned int> selected_indices(new_size);

      assert(pool_size <= pop_size &&
       "ERROR: the bracket size is bigger than population size.");

      // Selecting new individuals
      for (std::size_t i = 0; i < new_size; ++i) 
      {
        bracket.clear();
        std::size_t winner_index = 0;
        double winner_fitness = 0;

        // Creates the bracket
        for (std::size_t j = 0; j < pool_size; ++j) 
        {
          bracket[j] = nevil::random::random_int(pop_size);
          // Ensures that the same individual is not put in the bracket more than once
          for (std::size_t k = 0; k < j; ++k)
          {
            if (bracket[j] == bracket[k])
            {
              bracket[j] = nevil::random::random_int(pop_size);
              k = 0;
              continue;
            }
            // Select the individual with higher fitness
            if (start[bracket[j]]->get_fitness() > winner_fitness)
            {
              winner_index = bracket[j];
              winner_fitness = start[bracket[j]]->get_fitness();
            }
          }
        }
        selected_indices[i] = winner_index;
      }
      return selected_indices;
    }
  }
}

#endif // _NEVIL_UTIL_EVOLUTION_HPP_
