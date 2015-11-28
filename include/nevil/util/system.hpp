#ifndef _NEVIL_UTIL_SYSTEM_HPP_
#define _NEVIL_UTIL_SYSTEM_HPP_

#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <string>

#ifdef _WIN32
  #define OS_SEP '\\'
  #include <windows.h>
  #include <direct.h>
  #define get_current_dir _getcwd
#else
  #define OS_SEP '/'
  #include <unistd.h>
  #define get_current_dir getcwd
#endif

namespace nevil
{
  namespace os
  {
    /**
    * Appends two directory paths. (OS safe)
    * @param std::string path1
    * @param std::string path2
    * @return std::string resulting path
    */
    std::string append_path(const std::string &path1, const std::string &path2);

    /**
    * Creates a directory if it doesn't exists.
    * @param std::string directory path
    * @return true new directory was created. False if directory exists or don't have permission
    * The status code would be zero if directory exits.
    */
    bool create_directory(const std::string &path);

    /**
    * Constructs a directory nevil based on the current time.
    * @param
    * @return std::string directory nevil
    */
    std::string get_time_name_dir();

    /**
    * Returns the current working directory of the binary file.
    * @param
    * @return std::string path to the current working directory
    */
    std::string get_working_dir();
    
    /**
    * Returns the number of processors online.
    * @param
    * @return int number of online processors.
    */
    int get_num_processors();
  }
}

#endif // _NEVIL_UTIL_SYSTEM_HPP_
