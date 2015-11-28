#ifndef _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_
#define _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_

#include <cassert>
#include <cstdlib>
#include <vector>

namespace nevil
{
  class basic_feedforward_nn
  {
   public:
    basic_feedforward_nn();
    basic_feedforward_nn(std::size_t input_num, std::size_t num_output_nodes);
    basic_feedforward_nn(std::size_t input_num, std::size_t num_output_nodes
      , const std::vector<double> &weights);

    void set_weights(const std::vector<double> &weights);
    std::vector<double> update(const std::vector<double> &inputs);

   protected:
    std::size_t _num_input_nodes;
    std::size_t _num_output_nodes;
    std::vector<double> _weights;
  };
}

#endif // _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_
