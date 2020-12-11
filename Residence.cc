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
      costToImprove{{GLASS, 2}, {HEAT, 3}},  
      owner{owner} {};

Residence::Residence(shared_ptr<Builder> builderPtr, char type)
    : owner{builderPtr}, type{type} {
  switch (type) {
  case 'B':
    reward = 1;
    cost = {{BRICK, 1}, {ENERGY, 1}, {GLASS, 1}};
    costToImprove = {{GLASS, 2}, {HEAT, 3}};
    break;
  case 'H':
    reward = 2;
    cost = {{BRICK, 1}, {ENERGY, 1}, {HEAT, 3}, {GLASS, 3}};
    costToImprove = {{BRICK, 3}, {ENERGY, 2}, {GLASS, 2}, {WIFI, 1}, {HEAT, 2}};
    break;
  case 'T':
    reward = 3;
    cost = {{BRICK, 4}, {ENERGY, 3}, {HEAT, 5}, {GLASS, 5}, {WIFI, 1}};
    costToImprove = {};
    break;
  }
}

char Residence::getType() { return type; }

shared_ptr<Builder> Residence::getOwner() { return owner; }

int Residence::getReward() { return reward; }

void Residence::improveResidence(int vertexNum) {
  if (type == 'T') {
    throw logic_error("Residence::improveResidence: Tower can't be upgraded");
  }

  bool enoughResources = owner->checkResources(costToImprove);
  
  if(!enoughResources){
    throw logic_error("You don't have enough resources to upgrade that residence");
  }

  // Builder has enough resources, make changes
  if(type == 'B'){
      type = 'H';
      reward = 2;
      cost = {{BRICK, 1}, {ENERGY, 1}, {HEAT, 3}, {GLASS, 3}, {WIFI, 1}};
      owner->updateResidence(vertexNum,type, costToImprove);
      costToImprove = {{GLASS 2}, {HEAT, 3}};
  } 
  else if (type == 'H') {
      type = 'T';
      reward = 3;
      cost = {{BRICK, 4}, {ENERGY, 3}, {HEAT, 5}, {GLASS, 5}, {WIFI, 2}};
      owner->updateResidence(vertexNum,type, costToImprove);
      costToImprove = {{BRICK, 3}, {ENERGY, 2}, {GLASS, 2}, {WIFI, 1}, {HEAT, 2}};
  } 
  else {
    throw invalid_argument("Invalid housing typed passed to Residence class");
  }

  return type;
}

map<ResourceType, int> Residence::getCost() { return cost; }
