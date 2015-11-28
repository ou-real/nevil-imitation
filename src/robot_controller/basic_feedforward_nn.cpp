#include "nevil/robot_controller/basic_feedforward_nn.hpp"

nevil::basic_feedforward_nn::basic_feedforward_nn() {}

nevil::basic_feedforward_nn::basic_feedforward_nn(std::size_t input_num, std::size_t num_output_nodes)
  : _num_input_nodes(input_num)
  , _num_output_nodes(num_output_nodes)
  , _weights(std::vector<double>(_num_input_nodes * _num_output_nodes, 0))
  {}

nevil::basic_feedforward_nn::basic_feedforward_nn(std::size_t input_num, std::size_t num_output_nodes
  , const std::vector<double> &weights)
: _num_input_nodes(input_num)
, _num_output_nodes(num_output_nodes)
, _weights(weights)
{
  assert ((_num_input_nodes * _num_output_nodes) == weights.size()
  && "Error: matrix size and weight size don't match!");
}

void nevil::basic_feedforward_nn::set_weights(const std::vector<double> &weights)
{
  assert ((_num_input_nodes * _num_output_nodes) == weights.size()
    && "Error: matrix size and weight size don't match!");

  _weights = weights;
}

std::vector<double> nevil::basic_feedforward_nn::update(const std::vector<double> &inputs)
{
  assert ((_num_input_nodes == inputs.size())
    && "Error: matrix size and input size don't match!");

  std::vector<double> outputs(_num_output_nodes, 0);
  for (std::size_t i = 0; i < _num_output_nodes; ++i)
    for (std::size_t j = 0; j < _num_input_nodes; ++j)
        outputs[i] += _weights[(i * _num_input_nodes) + j] * inputs[j];
  return outputs;
}
