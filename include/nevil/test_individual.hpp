#ifndef _NEVIL_TEST_INDIVIDUAL_HPP_
#define _NEVIL_TEST_INDIVIDUAL_HPP_

#include "individual.hpp"

namespace nevil
{
  class test_individual : public individual
  {
  public:
    // Constructors
    test_individual();
    test_individual(std::size_t chromo_size);
    test_individual(const nevil::chromosome &chromo);

    // Mandatory virtual functions
    nevil::test_individual* clone() const;
  };
}

#endif // _NEVIL_TEST_INDIVIDUAL_HPP_
