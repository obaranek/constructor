#ifndef __EDGE_H_
#define __EDGE_H_

#include <map>
#include <memory>
#include <vector>

#include "Colour.h"
#include "ResourceType.h"
#include "Vertex.h"

class Builder;

class Edge {
private:
  int edgeNumber;
  bool hasRoad;
  std::shared_ptr<Builder> owner;
  std::vector<int> vertices;
  std::vector<int> adjacentEdges;
  std::map<ResourceType, int> cost;

public:
  Edge(int);

  // buildRoad() adds a Road object to the edge and calls the builder's
  // buildRoad function
  void buildRoad(const std::vector<std::shared_ptr<Vertex>> allVertices,
                 const std::vector<std::shared_ptr<Edge>> allEdges,
                 std::shared_ptr<Builder> builderPtr, bool free);

  // hasRoad() returns true if there is a road at this edge
  bool doesHaveRoad();

  /***** Getters and Setters *****/

  // getEdgeNum() returns the edge number
  int getEdgeNum();

  // getOwnerColour() returns the owner's Colour
  Colour getOwnerColour();

  friend class BoardModel;
};

#endif // __EDGE_H_
