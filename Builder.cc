#include "Builder.h"
#include "ResourceType.h"
#include <iostream>

#include <algorithm>
#include <map>

using namespace std;

Builder::Builder(Colour colour)
    : colour{colour}, points{0}, dice{'L'}, resources{{HEAT, 0},
                                                      {BRICK, 0},
                                                      {ENERGY, 0},
                                                      {GLASS, 0},
                                                      {WIFI, 0}} {}

void Builder::buildResidence(int vertexNum, char residenceType,
                             map<ResourceType, int> cost, bool free) {
  
  buildings.insert(pair<int, char>(vertexNum, 'B'));
  points++;
  
  if(!free){
    for (auto &elem : cost) {
      int resourceCost = cost[elem.first];
      resources[elem.first] -= resourceCost;
    }
  }
}

void Builder::buildRoad(int edgeNum, std::map<ResourceType,int> cost, bool free ) {
  roads.emplace_back(edgeNum); 
  if(!free){
    for(auto &elem : cost){
      int resCost = cost[elem.first];
      resources[elem.first] -= resCost;
    }
  }
}

void Builder::updateResidence(int vertexNum, char residenceType) {
  buildings[vertexNum] = residenceType;
}

void Builder::takeResources(ResourceType type, int reward) {
  resources[type] += reward;
}

bool Builder::haveResidence(int vertexNum) {
  auto vertexIt = buildings.find(vertexNum);
  return vertexIt != buildings.end();
}

bool Builder::haveRoad(int edgeNum) {
  auto edgeIt = find(roads.begin(), roads.end(), edgeNum);
  return edgeIt != roads.end();
}

bool Builder::checkResources(map<ResourceType, int> requiredResources) {
  bool haveEnough = true;

  // Loop through the required resources
  for (auto reqResIt = requiredResources.begin();
       reqResIt != requiredResources.end(); reqResIt++) {
    auto myResIt = resources.find(reqResIt->first);
    int myResQuantity = myResIt->second;   // quantity in my storage
    int reqResQuantity = reqResIt->second; // quantity needed

    if (myResQuantity < reqResQuantity) {
      haveEnough = false;
      break;
    }
  }
  return haveEnough;
}

/***** Setters and Getters *****/

Colour Builder::getColour() { return colour; }

int Builder::getPoints() { return points; }

char Builder::getDiceType() { return dice; }

map<ResourceType, int> &Builder::getResources() { return resources; }

map<int, char> &Builder::getBuildings() { return buildings; }

void Builder::setDice(char diceType) { dice = diceType; }
