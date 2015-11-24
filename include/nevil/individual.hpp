#ifndef _NAME_INDIVIDUAL_HPP_
#define _NAME_INDIVIDUAL_HPP_

#include <vector>

namespace nevil
{
  class individual
  {
  public:
    virtual void increase_fitness(double fitness) = 0;
    virtual void mutate(double rate) = 0;
    virtual individual* clone() const = 0;

    double get_fitness() const { return _fitness; };
    const std::vector<double> &get_chromosome() const { return _chromosome; }
    bool operator> (const individual &rhs) { return _fitness > rhs._fitness; }
    bool operator< (const individual &rhs) { return _fitness < rhs._fitness; }

  protected:
    double _fitness;
    std::vector<double> _chromosome;
  };
}

#endif // _INDIVIDUAL_HPP_
