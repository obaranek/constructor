#include <stdexcept>

#include "../include/Builder.h"
#include "../include/Colour.h"
#include "../include/Edge.h"

using namespace std;

Edge::Edge(int edgeNumber)
    : edgeNumber{edgeNumber}, hasRoad{false}, cost{{HEAT, 1}, {WIFI, 1}} {};

void Edge::buildRoad(const std::vector<std::shared_ptr<Vertex>> allVertices,
                     const std::vector<std::shared_ptr<Edge>> allEdges,
                     std::shared_ptr<Builder> builderPtr, bool free) {

  // check if we want free road (only called when loading a game)
  if (free) {
    hasRoad = true;
    owner = builderPtr;
    builderPtr->buildRoad(edgeNumber, cost, free);
    return;
  }

  bool enoughResources = builderPtr->checkResources(cost);
  if (!enoughResources) {
    throw logic_error("You don't have enough resources to build a road");
  }

  // check if edge already has a road
  if (hasRoad) {
    throw logic_error("Edge already has a road");
  }

  bool canBuild = false;
  for (int adjacentVertex : vertices) {
    if (builderPtr->haveResidence(adjacentVertex)) {
      canBuild = true;
    } else if (allVertices.at(adjacentVertex)->getResidence() == nullptr) {
      for (auto &adjacentEdge : allVertices.at(adjacentVertex)->getEdges()) {
        if (allEdges.at(adjacentEdge)->owner == builderPtr) {
          canBuild = true;
        }
      }
    }
  }

  if (canBuild) {
    hasRoad = true;
    owner = builderPtr;
    builderPtr->buildRoad(edgeNumber, cost, free);
  } else {
    throw logic_error("You must have adjacent edge that is not blocked or "
                      "vertex to build a road");
  }
}

bool Edge::doesHaveRoad() { return hasRoad; }

/***** Getters and Setters *****/

int Edge::getEdgeNum() { return edgeNumber; }

Colour Edge::getOwnerColour() { return owner->getColour(); }
