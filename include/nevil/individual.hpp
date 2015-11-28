#ifndef _NEVIL_INDIVIDUAL_HPP_
#define _NEVIL_INDIVIDUAL_HPP_

#include <vector>

namespace nevil
{
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

    // Mandatory virtual functions
    virtual void mutate(double rate) = 0;
    virtual nevil::individual* clone() const = 0;
    
    // Getters
    double get_fitness() const;
    const std::vector<double> &get_chromosome() const;

    // Comparators (equality for individual really doesn't make sense. Equal genes??)
    bool operator>(const individual &rhs) const;
    bool operator<(const individual &rhs) const;

  protected:
    double _fitness;
    std::vector<double> _chromosome;
  };
}

#endif // _NEVIL_INDIVIDUAL_HPP_
