#ifndef _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_
#define _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_

#include <cassert>
#include <cstdlib>
#include <vector>
#include "nevil/robot_controller/basic_nn.hpp"

namespace nevil
{
  class basic_feedforward_nn : public basic_nn
  {
   public:
    basic_feedforward_nn(std::size_t input_num, std::size_t num_output_nodes);
    basic_feedforward_nn(std::size_t input_num, std::size_t num_output_nodes
      , const std::vector<double> &weights);

    void set_weights(const std::vector<double> &weights);
    std::vector<double> get_outputs(const std::vector<double> &inputs);
    std::vector<double> update(const std::vector<double> &inputs, const std::vector<double> &expected_outputs = std::vector<double>());
  };
}

#endif // _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_
