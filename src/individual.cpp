#include "nevil/individual.hpp"

nevil::individual::individual()
 : _fitness(0)
{}

nevil::individual::individual(std::size_t chromo_size)
  : _fitness(0)
  , _chromosome(nevil::chromosome(chromo_size, 0))
{}

nevil::individual::~individual()
{}

void nevil::individual::increase_fitness(double fitness)
{
  _fitness += fitness;
}

void nevil::individual::decrease_fitness(double fitness)
{
  _fitness -= fitness;
}

void nevil::individual::set_fitness(double fitness)
{
  _fitness = fitness;
}

double nevil::individual::get_fitness() const
{
  return _fitness;
}

const nevil::chromosome &nevil::individual::get_chromosome() const
{
  return _chromosome;
}

void nevil::individual::mutate(double rate)
{
  assert ((0 <= rate && rate <= 1) && "Mutation rate must be between 0 and 1");
  if (nevil::random::random_double() <= rate)
  {
    int gene_index = nevil::random::random_int() % (_chromosome.size());
    _chromosome[gene_index] = nevil::random::random_int(-15, 15);
  }
}

bool nevil::individual::operator>(const individual &rhs) const
{
  return _fitness > rhs._fitness;
}

bool nevil::individual::operator<(const individual &rhs) const
{
  return _fitness < rhs._fitness;
}
