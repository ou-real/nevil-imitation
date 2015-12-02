#ifndef NEVIL_UTIL_JSON_LOGGER_HPP_
#define NEVIL_UTIL_JSON_LOGGER_HPP_

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include "nevil/util/system.hpp"

namespace nevil
{
  class json_logger
  {
  public:
    inline json_logger() {
      _output_file = new std::ofstream();
    };

    inline void start_new_file(const std::string &path, const std::string &file_name)
    {
      if (_output_file->is_open())
          _output_file->close();

      std::string file_path = os::append_path(path, file_name);
      _output_file->open(file_path.c_str(), std::ofstream::out);

      if (!(*_output_file))
      {
        std::cerr << "Failed to open the file \"" << file_path << "\"\nAborting now..." << std::endl;
        std::abort();
      }
    }

    inline void flush()
    {
      _output_file->flush();
    }

    inline void close_file()
    {
      _output_file->close();
    }

    inline void write(const Json::Value &root)
    {
      Json::StyledStreamWriter writer;
      writer.write(*_output_file, root);
    }

  protected:
      std::ofstream *_output_file;
  };
}

#endif // NEVIL_UTIL_JSON_LOGGER_HPP_
