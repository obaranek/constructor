#include "Builder.h"
#include "ResourceType.h"

using namespace std;

bool Builder::checkResidenceResource() {
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


void Builder::buildResidence(int vertexNum){
  buildings.insert(pair<int, char>(vertexNum, 'B'));
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

/***** Setters and Getters *****/

Colour Builder::getColour(){
  return colour;
}

int Builder::getPoints(){
  return points;
}
