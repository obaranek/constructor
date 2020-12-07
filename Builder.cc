#include "Builder.h"
#include "ResourceType.h"

#include <algorithm>

using namespace std;

Builder::Builder(Colour colour) 
  : colour{colour}, points{0}, dice{'L'} {}


bool Builder::checkResidenceResources() {
  // Basement costs;
  // 1 BRICK, 1 ENERGY, 1 GLASS, 1 WIFI

  auto brickIt = resources.find(ResourceType::BRICK);
  auto energyIt = resources.find(ResourceType::ENERGY);
  auto glassIt = resources.find(ResourceType::GLASS);
  auto wifiIt = resources.find(ResourceType::WIFI);

  if(*brickIt < 1){
    return false;
  }

  if(*energyIt < 1){
    return false;
  }

  if(*glassIt < 1){
    return false;
  }

  if(*wifiIt < 1){
    return false;
  }

  return true;
}


bool Builder::checkRoadResources() {
  // Road costs;
  // 1 HEAT, 1 WIFI

  auto wifiIt = resources.find(ResourceType::WIFI);
  auto heatIt = resources.find(ResourceType::HEAT);

  if(*wifiIt < 1){
    return false;
  }

  if(*heatIt < 1){
    return false;
  }

  return true;
}


void Builder::buildResidence(int vertexNum){
  buildings.insert(pair<int, char>(vertexNum, 'B'));
}


void Builder::buildRoad(int edgeNum){
  roads.emplace_back(edgeNum);
}


void Builder::updateResidence(int vertexNum, char residenceType){
  // change the buildingType at vertexNum 
  auto itr = buildings.find(vertexNum);
  if(itr != buildings.end()){
    itr->second = residenceType; 
  }else{
    //@TODO: Throw exception: Builder doesn't own the vertex
  }
}

void Builder::takeResources(ResourceType type, int reward){
  auto resourceIt = resources.find(type);
 if(resourceIt != resources.end()){
  resourceIt->second = reward;
 }
 else{
  // @TODO: Throw exception: ResourceType not valid
 }
} 

bool Builder::haveResidence(int vertexNum){
  auto vertexIt = buildings.find(vertexNum);
  return vertexIt != buildings.end();
}

bool Builder::haveRoad(int edgeNum){
  auto edgeIt =  find(roads.begin(), roads.end(), edgeNum);
  return edgeIt != roads.end();
}


bool checkResources(map<ResourceType,int>& requiredResources){
  bool haveEnough = true;
  
  // Loop through the required resources
  for( auto reqResIt = requiredResources.begin(); reqResIt != requiredResources.end(); reqResIt++){
    auto myResIt = resources.find(reqResIt->first);
    int myResQuantity = myResIt->second; // quantity in my storage
    int reqResQuantity = reqResIt->second; // quantity needed

    if(myResQuantity < reqResQuantity) {
      haveEnough = false;
      break;
    }
  }
  return haveEnough;
}


/***** Setters and Getters *****/

Colour Builder::getColour() { return colour; }

int Builder::getPoints(){ return points; }

char Builder::getDiceType() { return dice; }

map<ResourceType,int>& Builder::getResources() { return resources; }

map<int, char>& Builder::getBuildings() { return buildings; }

void setDice(char diceType) { dice = diceType; }
