#include "nevil/robot_controller/basic_nn.hpp"


nevil::basic_nn::basic_nn(std::size_t input_num, std::size_t num_output_nodes)
  : _num_input_nodes(input_num)
  , _num_output_nodes(num_output_nodes)
  , _weights(std::vector<double>(_num_input_nodes * _num_output_nodes, 0))
  {}

nevil::basic_nn::basic_nn(std::size_t input_num, std::size_t num_output_nodes
  , const std::vector<double> &weights)
: _num_input_nodes(input_num)
, _num_output_nodes(num_output_nodes)
, _weights(weights)
{
  assert ((_num_input_nodes * _num_output_nodes) == weights.size()
  && "Error: matrix size and weight size don't match!");
}

void nevil::basic_nn::set_weights(const std::vector<double> &weights)
{
  assert ((_num_input_nodes * _num_output_nodes) == weights.size()
    && "Error: matrix size and weight size don't match!");

  _weights = weights;
}