#include "Edge.h"
#include "Builder.h"
#include "Colour.h"

using namespace std;

Edge::Edge(int edgeNumber)
  : edgeNumber{edgeNumber}, hasRoad{false} {};

void Edge::buildRoad(shared_ptr<Builder> builderPtr){
  
  // check if edge already has a road
  if(hasRoad){
    //@TODO: Throw exception- Edge already has a road
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
    builderPtr->buildRoad(edgeNumber);
  }else{
    //@TODO: Throw exception- No adjacent edge or vertex
  }
}

bool Edge::hasRoad(){
  return hasRoad;
}

/***** Getters and Setters *****/

int Edge::getEdgeNum() { return number; }

Colour getOwnerColour() {
  return owner->getColour();
}
