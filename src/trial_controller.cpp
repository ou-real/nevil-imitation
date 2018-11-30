#include "nevil/trial_controller.hpp"

nevil::trial_controller::trial_controller() {}

nevil::trial_controller::trial_controller(int id, unsigned seed, const nevil::args &cl_args)
  : _trial_id(id)
{
  srand(seed);

  //Default Values
  _population_size = 80;
  _max_generation_num = 200;
  _max_step_num = 1000;
  std::string trial_name = "TestTrial";
  double mutation_rate = 0.25;
  double bracket_ratio = 0.1;

  // Reading the command line arguments
  nevil::args::const_iterator it;
  nevil::args local_args(cl_args);

  if ((it = local_args.find("xn")) != local_args.end())
    trial_name = it->second;

  if ((it = local_args.find("mg")) != local_args.end())
    _max_generation_num = stoi(it->second);

  if ((it = local_args.find("ms")) != local_args.end())
    _max_step_num = stoi(it->second);

  if ((it = local_args.find("ps")) != local_args.end())
    _population_size = stoi(it->second);
  else
    local_args["ps"] = std::to_string(_population_size);

  if ((it = local_args.find("br")) != local_args.end())
  {
    bracket_ratio = stof(it->second);
    if (bracket_ratio < 0 || bracket_ratio > 1)
    {
      printf("Bracket ratio must be between 0 and 1. '%.2f' was given.\nTerminating ...", bracket_ratio);
      exit(-1); 
    }
  }
  else
    local_args["br"] = std::to_string(bracket_ratio);

  if ((it = local_args.find("mr")) != local_args.end())
  {
    mutation_rate = stof(it->second);
    if (mutation_rate < 0 || mutation_rate > 1)
    {
      printf("Mutation rate must be between 0 and 1. '%.2f' was given.\nTerminating ...", mutation_rate);
      exit(-1); 
    }
  }
  else
    local_args["mr"] = std::to_string(mutation_rate);


  // Actor Observer Neuron Parameter
  if ((it = cl_args.find("sn")) != cl_args.end())
    _root["config"]["actorObserverNeuron"] = (it->second == "true");
  else
    local_args["sn"] = "false";

  //Speed Parameter
  if ((it = cl_args.find("speedA")) != cl_args.end())
    _root["config"]["speedA"] = std::stod(it->second);
  else
    local_args["speedA"] = "12";

  if ((it = cl_args.find("speedO")) != cl_args.end())
    _root["config"]["speedO"] = std::stod(it->second);
  else
    local_args["speedO"] = "12";


  //Angle Parameter
  if ((it = cl_args.find("angleA")) != cl_args.end())
    _root["config"]["angleA"] = std::stod(it->second);
  else
    local_args["angleA"] = "3";

  if ((it = cl_args.find("angleO")) != cl_args.end())
    _root["config"]["angleO"] = std::stod(it->second);
  else
    local_args["angleO"] = "3";

  // Creating a log file
  // Logging into a text file example
  _trial_logger.start_new_file(local_args["xp_path"], "Trial_" + std::to_string(_trial_id) + ".txt");
  // Logging json example
  _trial_json_logger.start_new_file(local_args["xp_path"], "Trial_" + std::to_string(_trial_id) + ".json");
  _generational_data = Json::Value(Json::arrayValue);

  // Output arguments to file
  // Text style
  _trial_logger << "==Config==" << std::endl;
  _trial_logger << "-Name: " << trial_name << std::endl;
  _trial_logger << "-Random seed: " << seed << std::endl;
  _trial_logger << "-Number of generations: " << _max_generation_num << std::endl;
  _trial_logger << "-Number of timesteps: " << _max_step_num << std::endl;
  _trial_logger << "-Population size: " << _population_size << std::endl;
  _trial_logger << "-Bracket Ratio: " << bracket_ratio << std::endl;
  _trial_logger << "-Mutation Rate: " << mutation_rate << std::endl;
  _trial_logger << "==Starting Trial==" << std::endl;

  
  // JSON style
  _root["config"]["trialName"] = trial_name;
  _root["config"]["randomSeed"] = seed;
  _root["config"]["numberOfGenerations"] = _max_generation_num;
  _root["config"]["numberOfTimesteps"] = _max_step_num;
  _root["config"]["populationSize"] = _population_size;
  _root["config"]["bracketRatio"] = bracket_ratio;
  _root["config"]["mutationRate"] = mutation_rate;

  // Instantiating a controller
  // If you have more than one controller you can use the controller name to instantiate the right one
  _trial = nevil::actor_observer_trial(local_args);

  _current_generation = 0;
  _current_individual = 0;
  _current_step = 0;
  printf("-Trial %d: starting\n", _trial_id);
  printf("-Trial %d: running generation %d\n", _trial_id, _current_generation);
}

Enki::World *nevil::trial_controller::get_world() const
{
  return _trial.get_world();
}

bool nevil::trial_controller::run()
{
  if (_current_generation < _max_generation_num)
  {
    if (_current_individual < _population_size)
    {
      if (_current_step == 0 && _current_individual != _population_size)
        _trial.reset();

      if (_current_step < _max_step_num)
      {
        _trial.update();
        ++_current_step;
      }
      else
      {
        ++_current_individual;
        _current_step = 0;
      }
    }
    else
    {
      _evaluate();
      ++_current_generation;
      _current_individual = 0;
      _current_step = 0;
      printf("-Trial %d: running generation %d\n", _trial_id, _current_generation);
    }
    return true;
  }

  _end();
  return false;
}


void nevil::trial_controller::_evaluate()
{
  _trial.epoch();
  // Text logging
  _trial_logger << _current_generation << "\t" << _trial.get_best_individuals().at(0).get_fitness() << std::endl;
  _trial_logger << _current_generation << "\t" << _trial.get_best_individuals().at(1).get_fitness() << std::endl;

  //JSON logging
  Json::Value data;
  data["generationNumber"] = _current_generation;
  data["maxFitnessActor"] = _trial.get_best_individuals().at(0).get_fitness();
  data["maxFitnessObserver"] = _trial.get_best_individuals().at(1).get_fitness();
  _generational_data.append(data);
}

void nevil::trial_controller::_end()
{
  printf("-Trial %d: finished\n", _trial_id);
  //Text logging
  _trial_logger << "==Trial Ended==" << std::endl;
  _trial_logger << "Best actor chromosome " << _trial.get_best_individuals().at(0).get_chromosome() << std::endl;
  _trial_logger << "Best observer chromosome " << _trial.get_best_individuals().at(1).get_chromosome() << std::endl;
  _trial_logger.close_file();

  //JSON logging
  Json::Value best_actor_chromosome (Json::arrayValue);
  auto best_actor_chromosome_vec = _trial.get_best_individuals().at(0).get_chromosome();
  for (int i = 0; i < best_actor_chromosome_vec.size(); ++i)
    best_actor_chromosome.append(best_actor_chromosome_vec[i]);

  Json::Value best_observer_chromosome (Json::arrayValue);
  auto best_observer_chromosome_vec = _trial.get_best_individuals().at(1).get_chromosome();
  for (int i = 0; i < best_actor_chromosome_vec.size(); ++i)
    best_observer_chromosome.append(best_actor_chromosome_vec[i]);

  _root["generationalData"] = _generational_data;
  _root["bestActorChromosome"] = best_actor_chromosome;
  _root["bestObserverChromosome"] = best_observer_chromosome;
  _trial_json_logger.write(_root);
  _trial_json_logger.close_file();
}