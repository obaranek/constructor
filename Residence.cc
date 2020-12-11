#include "Residence.h"
#include "Builder.h"
#include "ResourceType.h"

#include <map>
#include <stdexcept>

using std::logic_error;
using std::invalid_argument;
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

void Residence::improveResidence() {
  if (type == 'T') {
    throw logic_error("Residence::improveResidence: Tower can't be upgraded");
  }

  bool enoughResources = false;

  if(type == 'B'){
    
    enoughResources = owner->checkResources({GLASS, 2}, {HEAT, 3});
    
    if(enoughResources){
      type = 'H';
      reward = 2;
      cost = {{BRICK, 1}, {ENERGY, 1}, {HEAT, 3}, {GLASS, 3}, {WIFI, 1}};
    }

  } else if (type == 'H') {
    
    enoughResources = owner->checkResources({{GLASS, 2}, {HEAT, 3}});
    
    if(enoughResources){
      type = 'T';
      reward = 3;
      cost = {{BRICK, 4}, {ENERGY, 3}, {HEAT, 5}, {GLASS, 5}, {WIFI, 2}};
    }
  } else {
    throw invalid_argument("Invalid housing typed passed to Residence class");
  }

  if(!enoughResources){
    throw logic_error("You don't have enough resources to upgrade that residence");
  }

  return type;
}

map<ResourceType, int> Residence::getCost() { return cost; }
