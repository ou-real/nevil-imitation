#ifndef _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_
#define _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_

#include <assert.h>
#include <vector>

namespace nevil
{
  class basic_feedforward_nn
  {
   public:
    basic_feedforward_nn();
    basic_feedforward_nn(size_t input_num, size_t num_output_nodes);

    void set_weights(const std::vector<double> &weights);
    std::vector<double> update(const std::vector<double> &inputs);

   protected:
    std::vector<double> _weights;
    size_t _num_input_nodes;
    size_t _num_output_nodes;
  };
}

#endif // _NEVIL_ROBOT_CONTROLLER_BASIC_FEEDFORWARD_NN_HPP_
