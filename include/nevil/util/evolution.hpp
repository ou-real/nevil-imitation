#ifndef _NEVIL_UTIL_EVOLUTION_HPP_
#define _NEVIL_UTIL_EVOLUTION_HPP_

#include <vector>

namespace nevil
{
  namespace evolution
  {
    template <class RandomAccessIterator>
    inline std::vector<int> tournament_selection(const RandomAccessIterator &start, const RandomAccessIterator &end, int new_size, size_t pool_size)
    {
      int pop_size = (end - start);
      std::vector<int> bracket(pool_size);
      std::vector<int> selected_indices(new_size);

      assert (pool_size <= pop_size && "ERROR: the bracket size is bigger than population size.\nTerminating...");

      // Selecting new individuals
      for (int i = 0; i < new_size; ++i) 
      {
        bracket.clear();
        int winner_index = 0;
        double winner_fitness = 0;

        // Creates the bracket
        for (int j = 0; j < pool_size; ++j) 
        {
          bracket[j] = rand() % pop_size;
          // Ensures that the same individual is not put in the bracket more than once
          for (int k = 0; k < j; ++k)
          {
            if (bracket[j] == bracket[k])
            {
              bracket[j] = rand() % pop_size;
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
