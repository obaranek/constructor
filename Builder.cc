#include "Builder.h"
#include "ResourceType.h"

using namespace std;

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


void Builder::improveResidence(int vertexNum, char residenceType){
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

/***** Setters and Getters *****/

Colour Builder::getColour(){
  return colour;
}

int Builder::getPoints(){
  return points;
}
