#include "Residence.h"

#include <stdexcept>

using std::invalid_argument;
using std::make_pair;

Residence::Residence(char type) {
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
