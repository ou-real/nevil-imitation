#include "nevil/robot_controller/delta_rule_nn.hpp"

nevil::delta_rule_nn::delta_rule_nn(std::size_t input_num, std::size_t num_output_nodes)
  : basic_nn(input_num, num_output_nodes)
  {}

nevil::delta_rule_nn::delta_rule_nn(std::size_t input_num, std::size_t num_output_nodes
  , const std::vector<double> &weights)
: basic_nn(input_num, num_output_nodes, weights)
{
  assert ((_num_input_nodes * _num_output_nodes) == weights.size()
  && "Error: matrix size and weight size don't match!");
}

/**
 * Outputs are restricted to 0.0 to 1.0
 */
std::vector<double> nevil::delta_rule_nn::get_outputs(const std::vector<double> &inputs)
{
  assert ((_num_input_nodes == inputs.size())
    && "Error: matrix size and input size don't match!");

  std::vector<double> outputs(_num_output_nodes, 0);
  for (std::size_t i = 0; i < _num_output_nodes; ++i)
  {
    double weighted_sum = 0;
    for (std::size_t j = 0; j < _num_input_nodes; ++j)
    {
        weighted_sum += _weights[(i * _num_input_nodes) + j] * inputs[j];
    }
    outputs[i] = activation_function(weighted_sum);
  }
  return outputs;
}

std::vector<double> nevil::delta_rule_nn::update(const std::vector<double> &inputs, const std::vector<double> &expect_outputs)
{
  return get_outputs(inputs); 
}


double nevil::delta_rule_nn::activation_function(double x)
{
  return(1 / (1 + exp(-x)));
}

double nevil::delta_rule_nn::activation_function_derivative(double x)
{
  double fvalue = activation_function(x);

  // This only holds for an activation function of (1 / (1 + exp(-x)))
  return(fvalue * (1 - fvalue));
}