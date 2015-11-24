#include "nevil/robot_controller/basic_feedforward_nn.hpp"

nevil::basic_feedforward_nn::basic_feedforward_nn() {}

nevil::basic_feedforward_nn::basic_feedforward_nn(size_t input_num, size_t num_output_nodes)
  : _num_input_nodes(input_num)
  , _num_output_nodes(num_output_nodes)
  , _weights(std::vector<double>(input_num * num_output_nodes, 0))
  {}

void nevil::basic_feedforward_nn::set_weights(const std::vector<double> &weights)
{
  assert ((_num_input_nodes * _num_output_nodes) == weights.size()
    && "ERROR: matrix size and weight size don't match!");

  _weights = weights;
}

std::vector<double> nevil::basic_feedforward_nn::update(const std::vector<double> &inputs)
{
  assert ((_num_input_nodes == inputs.size())
    && "ERROR: matrix size and input size don't match!");

  std::vector<double> outputs(_num_output_nodes, 0);
  for (size_t i = 0; i < _num_output_nodes; ++i)
    for (size_t j = 0; j < _num_input_nodes; ++j)
        outputs[i] += _weights[(i * _num_input_nodes) + j] * inputs[j];
  return outputs;
}
