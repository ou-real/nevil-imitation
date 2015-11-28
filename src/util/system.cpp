#include "nevil/util/system.hpp"

/**
* Appends two directory paths. (OS safe)
* @param std::string path1
* @param std::string path2
* @return std::string resulting path
*/
std::string nevil::os::append_path(const std::string &path1, const std::string &path2)
{
  return path1 + OS_SEP + path2;
}

/**
* Creates a directory if it doesn't exists.
* @param std::string directory path
* @return true new directory was created. False if directory exists or don't have permission
* The status code would be zero if directory exits.
*/
bool nevil::os::create_directory(const std::string &path)
{
  int status;
  #ifdef _WIN32
    status = mkdir(path.c_str());
  #else
    status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  #endif
  return (status == 0);
}

/**
* Constructs a directory nevil based on the current time.
* @param
* @return std::string directory nevil
*/
std::string nevil::os::get_time_name_dir()
{
  using namespace std::chrono;
  auto tt = system_clock::to_time_t(system_clock::now());
  tm now = *localtime(&tt);

  std::string time_dir_name = 
    std::to_string(now.tm_mon + 1)+ "-" 
  + std::to_string(now.tm_mday) + "-"
  + std::to_string(now.tm_year + 1900) + "_"
  + std::to_string(now.tm_hour) + "-"
  + std::to_string(now.tm_min) + "-"
  + std::to_string(now.tm_sec);

  return time_dir_name;
}

/**
* Returns the current working directory of the binary file.
* @param
* @return std::string path to the current working directory
*/
std::string nevil::os::get_working_dir()
{
  char current_path[FILENAME_MAX];
  if (!get_current_dir(current_path, FILENAME_MAX))
  {
    std::cerr << "Could not get the working directory" << std::endl;
    std::abort();
  }
  return std::string(current_path);
}

/**
* Returns the number of processors online.
* @param
* @return int number of online processors.
*/
int nevil::os::get_num_processors()
{
  int num_procesors;
  #ifdef _WIN32
    #ifndef _SC_NPROCESSORS_ONLN
      SYSTEM_INFO sys_info;
      GetSystemInfo(&sys_info);
      num_procesors = sys_info.dwNumberOfProcessors;
    #endif
  #endif

  #ifdef _SC_NPROCESSORS_ONLN
    num_procesors = sysconf(_SC_NPROCESSORS_ONLN);
  #endif

  return num_procesors;
}
