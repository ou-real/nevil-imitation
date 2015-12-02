#include "nevil/test_individual.hpp"

nevil::test_individual::test_individual()
  : nevil::individual()
{}

nevil::test_individual::test_individual(std::size_t chromo_size)
  : nevil::individual(chromo_size)
{
  // Assign values to every gene in the chromosome
  for (int i = 0; i < _chromosome.size(); ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::test_individual::test_individual(const nevil::chromosome &chromo)
  : nevil::individual()
{
  _chromosome = chromo;
}

nevil::test_individual *nevil::test_individual::clone() const
{
  return new test_individual(_chromosome);
}