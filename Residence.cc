#include "Residence.h"
#include "Builder.h"
#include "ResourceType.h"

#include <map>
#include <stdexcept>

using std::logic_error;
using std::map;
using std::shared_ptr;

Residence::Residence(std::shared_ptr<Builder> owner)
    : cost{{BRICK, 1}, {ENERGY, 1}, {GLASS, 1}}, reward{1}, type{'B'},
      owner{owner} {};

Residence::Residence(shared_ptr<Builder> builderPtr, char type)
    : owner{builderPtr}, type{type} {
  switch (type) {
  case 'B':
    reward = 1;
    cost = {{BRICK, 1}, {ENERGY, 1}, {GLASS, 1}};
    break;
  case 'H':
    reward = 2;
    cost = {{BRICK, 1}, {ENERGY, 1}, {HEAT, 3}, {GLASS, 3}};
    break;
  case 'T':
    reward = 3;
    cost = {{BRICK, 4}, {ENERGY, 3}, {HEAT, 5}, {GLASS, 5}, {WIFI, 1}};
    break;
  }
}

char Residence::getType() { return type; }

shared_ptr<Builder> Residence::getOwner() { return owner; }

int Residence::getReward() { return reward; }

char Residence::improveResidence() {
  if (type == 'T') {
    throw logic_error("Residence::improveResidence: Tower can't be upgraded");
  }
  //@TODO do checkResources
  if (!owner->checkResources(cost)) {
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

map<ResourceType, int> Residence::getCost() { return cost; }
