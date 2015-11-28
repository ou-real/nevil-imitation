#ifndef _NEVIL_TEST_INDIVIDUAL_HPP_
#define _NEVIL_TEST_INDIVIDUAL_HPP_

#include <string>
#include "individual.hpp"
#include "nevil/util/random.hpp"

namespace nevil
{
  class test_individual : public individual
  {
  public:
    // Constructors
    test_individual();
    test_individual(size_t chromo_size);
    test_individual(const std::vector<double> &chromosome);

    // Mandatory virtual functions
    nevil::test_individual* clone() const;
    void mutate(double rate);
  };
}

#endif // _NEVIL_TEST_INDIVIDUAL_HPP_
