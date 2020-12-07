#include "Residence.h"
#include "Builder.h"

#include <stdexcept>

using std::invalid_argument;
using std::logic_error;
using std::make_pair;

Residence::Residence() {
  switch (type) {
  case 'B':
    reward = 1;
    cost.emplace(make_pair(BRICK, 1), make_pair(ENERGY, 1),
                 make_pair(GLASS, 1));
    break;
  case 'H':
    reward = 2;
    cost.emplace(make_pair(HEAT, 3), make_pair(GLASS, 2));
    break;
  case 'T':
    reward = 3;
    cost.emplace(make_pair(BRICK, 3), make_pair(ENERGY, 2), make_pair(GLASS, 2),
                 make_pair(WIFI, 1), make_pair(HEAT, 2));
  default:
    throw invalid_argument("Residence::Residence: Invalid residence type");
  }
}

char Residence::getType() { return type; }

shared_ptr<Builder> Residence::getOwner() { return owner; }

int Residence::getReward() { return reward; }

char Residence::improveResidence(shared_ptr<Builder> builder) {
  if (type == 'T') {
    throw logic_error("Residence::improveResidence: Tower can't be upgraded");
  }
  if (!builder->checkResources(cost)) {
    throw logic_error(
        "Residence::improveResidence: Builder Doesn't have enough resources");
  }
  switch (type) {
  case 'B':
    type = 'H';
    reward = 2;
    cost.clear();
    cost.emplace(make_pair(HEAT, 3), make_pair(GLASS, 2));
    break;
  case 'H':
    type = 'T';
    reward = 3;
    cost.clear();
    cost.emplace(make_pair(BRICK, 3), make_pair(ENERGY, 2), make_pair(GLASS, 2),
                 make_pair(WIFI, 1), make_pair(HEAT, 2));
    break;
  }
  return type;
}
