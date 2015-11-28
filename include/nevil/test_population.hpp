#ifndef _NEVIL_TEST_POPULATION_HPP_
#define _NEVIL_TEST_POPULATION_HPP_

#include <vector>
#include <algorithm>
#include "nevil/test_individual.hpp"
#include "nevil/util/evolution.hpp"

namespace nevil
{
  class test_population
  {
  public:
    test_population();
    test_population(size_t pop_size, float bracket_ratio, float mutation_rate);
    virtual ~test_population();

    size_t size() const;
    nevil::test_individual next_generation();

    test_population &operator=(const test_population &rhs);
    test_individual *operator[](int i);

  protected:
    size_t _population_size;
    size_t _bracket_size;
    float _mutation_rate;
    std::vector <nevil::test_individual *> _individual_list;
  };
}

#endif // _NEVIL_TEST_POPULATION_HPP_