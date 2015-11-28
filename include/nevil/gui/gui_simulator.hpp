#ifndef _NEVIL_GUI_SIMULATOR_HPP_
#define _NEVIL_GUI_SIMULATOR_HPP_

#include <memory>
#include "nevil/util/parser.hpp"
#include "nevil/util/random.hpp"
#include "nevil/gui/view.hpp"
#include "nevil/trial_controller.hpp"

namespace nevil
{
  class gui_simulator
  {
   public:
    gui_simulator();
    explicit gui_simulator(const nevil::args &cl_args);
    gui_simulator(const nevil::gui_simulator &rhs) = delete;
    gui_simulator(nevil::gui_simulator &&rhs) noexcept = delete;

    nevil::gui_simulator &operator=(const nevil::gui_simulator &rhs) = delete;
    nevil::gui_simulator &operator=(nevil::gui_simulator &&rhs) noexcept = delete;
   private:
    nevil::trial_controller _controller;
    std::unique_ptr<nevil::view> _view;
  };
}

#endif  // _NEVIL_GUI_SIMULATOR_HPP_
