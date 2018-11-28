#include "nevil/actor_observer_individual.hpp"

// Constructors
nevil::actor_observer_individual::actor_observer_individual(){}

nevil::actor_observer_individual::actor_observer_individual(std::size_t chromo_size, bool is_actor)
  : nevil::individual(chromo_size)
  , _is_actor(is_actor)
  , _is_observer(!is_actor)
{
  _fitness = 0;  

  // Assign values to every gene in the chromosome
  for (int i = 0; i < _chromosome.size(); ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::actor_observer_individual::actor_observer_individual(const nevil::chromosome &chromo, bool is_actor)
  : nevil::individual()
  , _is_actor(is_actor)
  , _is_observer(!is_actor)
{
  _fitness = 0;
  _chromosome = chromo;
}

nevil::actor_observer_individual::actor_observer_individual(const nevil::actor_observer_individual &rhs)
  : _is_actor(rhs._is_actor)
  , _is_observer(rhs._is_observer)
  , _uuid(rhs._uuid)
{
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
}

// Destructor
nevil::actor_observer_individual::~actor_observer_individual(){}

// Clone
nevil::actor_observer_individual *nevil::actor_observer_individual::clone(bool is_actor) const
{
  nevil::actor_observer_individual* new_individual = new actor_observer_individual(_chromosome, is_actor);
  new_individual->_uuid = _uuid;
  return new_individual;
}

// Getters
const std::string &nevil::actor_observer_individual::get_uuid() const
{
  return _uuid;
}

bool nevil::actor_observer_individual::is_actor() const 
{
  return _is_actor;
}

bool nevil::actor_observer_individual::is_observer() const
{
  return _is_observer;
}

Json::Value nevil::actor_observer_individual::json() const
{
  Json::Value data;
  data["UUID"] = _uuid;
  data["fitness"] = _fitness;
  return data;
}

// Setters
void nevil::actor_observer_individual::set_id(int id)
{
  _uuid = std::to_string(id) + (_is_actor ? "A" : "O");
}

void nevil::actor_observer_individual::mutate(float rate)
{
  assert (0 <= rate && rate <= 1 && "Mutation rate must be between 0 and 1");
  int gene_index = rand() % (_chromosome.size());
  double r = ((double) rand() / (RAND_MAX));
  if (r <= rate){
    _chromosome[gene_index] = nevil::random::random_int(-15, 15);
  }
}

// Mandatory virtual functions
nevil::actor_observer_individual *nevil::actor_observer_individual::clone() const
{
  return new actor_observer_individual();
}

// Operators
nevil::actor_observer_individual &nevil::actor_observer_individual::operator=(const nevil::actor_observer_individual &rhs)
{
  _is_actor = rhs._is_actor;
  _is_observer = rhs._is_observer;
  _uuid = rhs._uuid;
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
  return(*this);
}