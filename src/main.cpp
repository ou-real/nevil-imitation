#include "nevil/util/system.hpp"
#include "nevil/util/parser.hpp"
#include <chrono>

// Default output path
const std::string DEFAULT_OUTPUT_PATH = "results";
void set_output_path(nevil::args &cl_args);

#ifdef GUI
#include <QApplication>
#include "nevil/gui/view.hpp"
#include "nevil/trial_controller.hpp"

/**
* Main for GUI simulator
*/
int main(int argc, char *argv[])
{

  using namespace nevil;

  QApplication app(argc, argv);
  args cl_args = parser::parse_cl_args(argc, argv);
  set_output_path(cl_args);

  srand(time(0));
  trial_controller _controller (1, rand(), cl_args);
  _controller.run();

  return app.exec();
}

#else

#include "nevil/parallel/parallel_simulator.hpp"

/**
* Main for parallel simulator
*/
int main(int argc, char *argv[])
{
  using namespace nevil;

  args cl_args = parser::parse_cl_args(argc, argv);
  set_output_path(cl_args);
  parallel::simulator(cl_args);
  return 0;
}

#endif

/**
* Creates and sets the result directory.
* @param nevil::Args parsed program arguments.
* @return
*/
void set_output_path(nevil::args &cl_args)
{
  using namespace nevil;
  // Set output directory to default if user didn't specify one.
  cl_args["output"] = DEFAULT_OUTPUT_PATH;
  os::create_directory(cl_args["output"]);

  // Creating the trial path directory
  cl_args["xp_path"] = os::append_path(cl_args["output"], os::get_time_name_dir());
  os::create_directory(cl_args["xp_path"]);
}
