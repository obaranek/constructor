#include "Residence.h"
#include "Builder.h"

#include <stdexcept>

using std::invalid_argument;
using std::logic_error;
using std::make_pair;

Residence::Residence()
    : reward{1}, type{'B'}, cost{{BRICK, 1}, {ENERGY, 1}, {GLASS, 1}} {};

char Residence::getType() { return type; }

shared_ptr<Builder> Residence::getOwner() { return owner; }

int Residence::getReward() { return reward; }

char Residence::improveResidence(shared_ptr<Builder> builder) {
  if (type == 'T') {
    throw logic_error("Residence::improveResidence: Tower can't be upgraded");
  }
  //@TODO do checkResources
  if (!builder->checkResources(cost)) {
    throw logic_error(
        "Residence::improveResidence: Builder Doesn't have enough resources");
  }
  switch (type) {
  case 'B':
    type = 'H';
    reward = 2;
    cost = {{HEAT, 3}, {GLASS, 2}};
    break;
  case 'H':
    type = 'T';
    reward = 3;
    cost = {{BRICK, 3}, {ENERGY, 2}, {HEAT, 2}, {GLASS, 2}, {WIFI, 1}};
    break;
  }
  return type;
}
