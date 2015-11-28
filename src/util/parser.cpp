#include "nevil/util/parser.hpp"

nevil::args nevil::parser::read_json(char* path)
{
  std::cout << "Reading config from \""<< path << "\"..." << std::endl;
  
  std::ifstream file(path);
  if(!file.is_open())
  {
    std::cerr << "Failed to open \""<< path << "\"" << std::endl;
    std::abort();
  }

  nevil::args cl_args;
  Json::Value root;
  Json::Reader reader;
  if(!reader.parse(file, root, false))
  {
    std::cerr << reader.getFormatedErrorMessages() << std::endl;
    std::abort();
  }
  file.close();

  for (Json::ValueIterator it = root.begin(); it != root.end(); ++it)
    cl_args[it.key().asString()] = it->asString();
  return cl_args;
}

nevil::args nevil::parser::read_cl(int argc, char *argv[])
{
  nevil::args cl_args;
  for (std::size_t i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-')
    {
      std::string arg_name = std::string(argv[i]);
      //Erasing the starting dash
      arg_name.erase(arg_name.begin());

      std::string arg_value = "true";
      cl_args[arg_name] = std::string(argv[++i]);
    }
  }
  return cl_args;
}

nevil::args nevil::parser::parse_cl_args(int argc, char *argv[])
{
    nevil::args cl_args;
    if(argc < 2)
      std::cerr << "Warning: No configuration found!" << std::endl;
    else if (std::string(argv[1]).find(".json") != std::string::npos)
      cl_args = read_json(argv[1]);
    else
      cl_args = read_cl(argc, argv);

    std::cout << "Arguments read:" << std::endl << cl_args;
    return cl_args;
}
