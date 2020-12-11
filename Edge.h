#ifndef __EDGE_H_
#define __EDGE_H_

#include <memory>
#include <vector>
#include <map>

#include "Colour.h"
#include "ResourceType.h"

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
    void buildRoad(std::shared_ptr<Builder> builderPtr, bool free);

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
