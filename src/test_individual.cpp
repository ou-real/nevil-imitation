#include "nevil/test_individual.hpp"

nevil::test_individual::test_individual() {}

nevil::test_individual::test_individual(size_t chromo_size)
{
  _fitness = 0;
  // Assign values to every gene in the chromosome
  _chromosome = std::vector<double>(chromo_size);
  for (int i = 0; i < chromo_size; ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::test_individual::test_individual(const std::vector<double> &chromosome)
{
  _fitness = 0;
  _chromosome = chromosome;
}

// Move to base
void nevil::test_individual::increase_fitness(double fitness)
{
  _fitness += fitness;
}

nevil::test_individual *nevil::test_individual::clone() const
{
  return new test_individual(_chromosome);
}

// static mutation rate??
void nevil::test_individual::mutate(double rate)
{
  assert ((0 <= rate && rate <= 1) && "Mutation rate must be between 0 and 1");
  int gene_index = rand() % (_chromosome.size());
  double r  = ((double) rand() / (RAND_MAX));
  if (r <= rate)
    _chromosome[gene_index] = nevil::random::random_int(-15, 15);
}
