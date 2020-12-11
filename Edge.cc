#include <stdexcept>

#include "Edge.h"
#include "Builder.h"
#include "Colour.h"

using namespace std;

Edge::Edge(int edgeNumber)
  : edgeNumber{edgeNumber}, hasRoad{false}, cost{{HEAT,1}, {WIFI,1}} {};

void Edge::buildRoad(shared_ptr<Builder> builderPtr, bool free){

  // check if we want free road (only called when loading a game)
  if(free){
    builderPtr->buildRoad(edgeNumber, cost, free);
    return;
  }

  // check if user has enough resources
  bool enoughResources = builderPtr->checkResources(cost);
  if(!enoughResources){
    throw logic_error("You don't have enough resources to build a road");
  }

  // check if edge already has a road
  if(hasRoad){
    throw logic_error("Edge already has a road"):
  }

  // Check if user has an adjacent residence or road
  bool hasAdjacentRoad = false;
  bool hasAdjacentResidence = false;

  for (auto vertexNum : vertices){
    if(builderPtr->haveResidence(vertexNum)){
      hasAdjacentResidence = true;
    }
  }

  for (auto adjacentEdgeNum : adjacentEdges){
    if(builderPtr->haveRoad(adjacentEdgeNum)){
      hasAdjacentRoad = true;
    }
  }

  if(hasAdjacentRoad || hasAdjacentResidence){
    hasRoad = true;
    owner = builderPtr;
    builderPtr->buildRoad(edgeNumber,cost, free);
  }else{
    throw logic_error("You must have adjacent edge or vertex to build a road");
  }
}

bool Edge::doesHaveRoad(){
  return hasRoad;
}

/***** Getters and Setters *****/

int Edge::getEdgeNum() { return edgeNumber; }

Colour Edge::getOwnerColour() {
  return owner->getColour();
}

