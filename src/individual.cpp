#include "nevil/individual.hpp"

nevil::individual::individual()
 : _fitness(0)
 , _chromosome(std::vector<double>())
{}

nevil::individual::individual(std::size_t chromo_size)
  : _fitness(0)
  , _chromosome(std::vector<double>(chromo_size, 0))
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

const std::vector<double> &nevil::individual::get_chromosome() const
{
  return _chromosome;
}

bool nevil::individual::operator>(const individual &rhs) const
{
  return _fitness > rhs._fitness;
}

bool nevil::individual::operator<(const individual &rhs) const
{
  return _fitness < rhs._fitness;
}