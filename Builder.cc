#include "Builder.h"
#include "ResourceType.h"

#include <algorithm>

using namespace std;

Builder::Builder(Colour colour) : colour{colour}, points{0}, dice{'L'} {}

void Builder::buildResidence(int vertexNum) {
  buildings.insert(pair<int, char>(vertexNum, 'B'));
  points++;
}

void Builder::buildRoad(int edgeNum) { roads.emplace_back(edgeNum); }

void Builder::updateResidence(int vertexNum, char residenceType) {
  // change the buildingType at vertexNum
  auto itr = buildings.find(vertexNum);
  if (itr != buildings.end()) {
    itr->second = residenceType;
  } else {
    //@TODO: Throw exception: Builder doesn't own the vertex
  }
}

void Builder::takeResources(ResourceType type, int reward) {
  auto resourceIt = resources.find(type);
  if (resourceIt != resources.end()) {
    resourceIt->second = reward;
  } else {
    // @TODO: Throw exception: ResourceType not valid
  }
}

bool Builder::haveResidence(int vertexNum) {
  auto vertexIt = buildings.find(vertexNum);
  return vertexIt != buildings.end();
}

bool Builder::haveRoad(int edgeNum) {
  auto edgeIt = find(roads.begin(), roads.end(), edgeNum);
  return edgeIt != roads.end();
}

bool Builder::checkResources(map<ResourceType, int> &requiredResources) {
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
