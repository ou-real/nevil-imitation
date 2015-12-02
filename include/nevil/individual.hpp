#ifndef _NEVIL_INDIVIDUAL_HPP_
#define _NEVIL_INDIVIDUAL_HPP_

#include <vector>
#include "nevil/util/random.hpp"

namespace nevil
{
  typedef std::vector<double> chromosome;

  class individual
  {
  public:
    // Constructors
    individual();
    explicit individual(std::size_t chromo_size);
    virtual ~individual();

    // Optional Virtual functions
    virtual void increase_fitness(double fitness);
    virtual void decrease_fitness(double fitness);
    virtual void set_fitness(double fitness);
    virtual void mutate(double rate);

    // Mandatory virtual functions
    virtual nevil::individual* clone() const = 0;
    
    // Getters
    double get_fitness() const;
    const nevil::chromosome &get_chromosome() const;

    // Comparators (equality for individual really doesn't make sense. Equal genes??)
    bool operator>(const individual &rhs) const;
    bool operator<(const individual &rhs) const;

  protected:
    double _fitness;
    nevil::chromosome _chromosome;
  };
}

#endif // _NEVIL_INDIVIDUAL_HPP_
