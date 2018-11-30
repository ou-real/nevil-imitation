#ifndef _NEVIL_ACTOR_OBSERVER_ROBOT_HPP_
#define _NEVIL_ACTOR_OBSERVER_ROBOT_HPP_


#include "nevil/arena/robot.hpp"
#include "nevil/robot_controller/basic_feedforward_nn.hpp"
#include "nevil/actor_observer_individual.hpp"

namespace nevil
{
  class actor_observer_robot : public robot
  {
  public:
    actor_observer_robot(double x, double y, double angle, bool actor_observer_neuron, double max_speed
      , const std::string &robot_name, const Enki::Color &color); // actor_observer_neuron is true if using 'unique neurons'

    nevil::robot *clone() const;
    std::vector<double> get_inputs(const nevil::object_list &objects); // Gets camera inputs, includes indivudual neuron inputs if enabled.
    std::vector<double> get_outputs(const std::vector<double>);
    bool update(const nevil::object_list &objects);
    void set_individual(nevil::individual *i);

    // nevil::actor_observer_robot &operator=(const nevil::actor_observer_robot &rhs);
    // nevil::actor_observer_robot &operator=(nevil::actor_observer_robot &&rhs) noexcept;
    
  protected:
    bool _actor_observer_neuron; // actor_observer_neuron is true if using 'unique neurons'
    nevil::actor_observer_individual *_individual;
    nevil::basic_nn *_neural_network;
  };
}



#endif // _NEVIL_ACTOR_OBSERVER_ROBOT_HPP_
