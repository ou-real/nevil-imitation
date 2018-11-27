#ifndef _NEVIL_ACTOR_OBSERVER_INDIVIDUAL_HPP_
#define _NEVIL_ACTOR_OBSERVER_INDIVIDUAL_HPP_

#include <json/json.h>
#include <string>

#include "individual.hpp"

namespace nevil
{
  class actor_observer_individual : public individual
  {
  public:
    // Constructors
    actor_observer_individual();
    actor_observer_individual(std::size_t chromo_size, bool is_actor);
    actor_observer_individual(const nevil::chromosome &chromo, bool is_actor);
    actor_observer_individual(const actor_observer_individual &rhs);

    // Destructor
    ~actor_observer_individual();

    // Clone 
    actor_observer_individual* clone(bool is_actor) const; // Returns a pointer to an individual created with the default constructor

    // Getters
    const std::string &get_uuid() const; // Returns a unique identifier for this individual, ending in A or O
    bool is_actor() const;     // Returns true if the individual is an actor
    bool is_observer() const;  // Returns true if the individual is an observer
    Json::Value json() const;  // Returns a JSON representation of this individual

    // Setters
    void set_id(int id); // Sets the id of this individual
    void mutate(float rate); // Possibly mutates a single randomly-selected gene to a random value

    // Mandatory virtual functions
    nevil::actor_observer_individual* clone() const;

    // Operators
    nevil::actor_observer_individual &operator=(const nevil::actor_observer_individual &rhs);

  protected:
    // Indicates whether the individual is an actor
    bool _is_actor;

    // Indicates whether the individual is an observer
    bool _is_observer;

    // Unique identifier for each actor/observer, followed by A or O
    std::string _uuid;

  };
}

#endif // _NEVIL_ACTOR_OBSERVER_INDIVIDUAL_HPP_
