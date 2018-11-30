#ifndef _NEVIL_ROBOT_CONTROLLER_BASIC_NN_HPP_
#define _NEVIL_ROBOT_CONTROLLER_BASIC_NN_HPP_

#include <cassert>
#include <cstdlib>
#include <vector>

namespace nevil
{
  class basic_nn
  {
   public:
    basic_nn(std::size_t input_num, std::size_t num_output_nodes);
    basic_nn(std::size_t input_num, std::size_t num_output_nodes
      , const std::vector<double> &weights);

    void set_weights(const std::vector<double> &weights);
    virtual std::vector<double> get_outputs(const std::vector<double> &inputs) = 0;
    virtual std::vector<double> update(const std::vector<double> &inputs, const std::vector<double> &expected_output = std::vector<double>()) = 0;

   protected:
    std::size_t _num_input_nodes;
    std::size_t _num_output_nodes;
    std::vector<double> _weights;
  };
}

#endif // _NEVIL_ROBOT_CONTROLLER_BASIC_NN_HPP_
