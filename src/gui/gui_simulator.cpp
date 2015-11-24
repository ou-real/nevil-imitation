#include "nevil/gui/gui_simulator.hpp"

nevil::gui_simulator::gui_simulator() {}

nevil::gui_simulator::gui_simulator(const nevil::args &cl_args)
{
  unsigned seed = rand();
  nevil::args local_args(cl_args);
  if (local_args.find("rs") != local_args.end())
    seed = std::stoll(local_args["rs"]);

  _controller = nevil::trial_controller(1, seed, local_args);
  _view.reset(new nevil::view(&_controller));
  _view->show();
}