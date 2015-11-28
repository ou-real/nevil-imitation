#include "nevil/test_individual.hpp"

nevil::test_individual::test_individual()
  : nevil::individual()
{}

nevil::test_individual::test_individual(size_t chromo_size)
  : nevil::individual(chromo_size)
{
  // Assign values to every gene in the chromosome
  for (int i = 0; i < _chromosome.size(); ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::test_individual::test_individual(const std::vector<double> &chromosome)
  : nevil::individual()
{
  _chromosome = chromosome;
}

nevil::test_individual *nevil::test_individual::clone() const
{
  return new test_individual(_chromosome);
}
 
void nevil::test_individual::mutate(double rate)
{
  assert ((0 <= rate && rate <= 1) && "Mutation rate must be between 0 and 1");
  if (nevil::random::random_double() <= rate)
  {
    int gene_index = nevil::random::random_int() % (_chromosome.size());
    _chromosome[gene_index] = nevil::random::random_int(-15, 15);
  }
}
