#ifndef _NEVIL_PARALLEL_THREAD_HPP_
#define _NEVIL_PARALLEL_THREAD_HPP_

#include <stdlib.h>
#include <string>
#include <algorithm>
#include <thread>

#include "nevil/util/parser.hpp"
#include "nevil/util/system.hpp"
#include "nevil/trial_controller.hpp"

namespace nevil
{
  namespace parallel
  {
    namespace thread
    {
      void simulator(const args &cl_args);
      void _run_trial(const nevil::args &cl_args, size_t start_id, size_t end_id, unsigned random_seed);
    }
  }
}

#endif //_NEVIL_PARALLEL_THREAD_HPP_