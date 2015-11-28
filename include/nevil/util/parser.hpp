#ifndef _NEVIL_UTIL_PARSER_HPP_
#define _NEVIL_UTIL_PARSER_HPP_

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <json/json.h>
#include "print.hpp"

namespace nevil
{
  typedef std::unordered_map<std::string, std::string> args;

  namespace parser
  {
    args parse_cl_args(int argc, char *argv[]);
    args read_json(char* path);
    args read_cl(int argc, char *argv[]);
  }
}

#endif // _NEVIL_UTIL_PARSER_HPP_
