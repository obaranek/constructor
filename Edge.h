#ifndef __EDGE_H_
#define __EDGE_H_

#include <memory>
#include <vector>

class Road;

class Edge {
private:
  int number;
  std::unique_ptr<Road> road;
  std::vector<int> vertices;

public:
  Edge(int);

  // checkRoad() checks if a road exists already (returns true if no road
  // exists)
  void checkRoad(int);

  // buildRoad() adds a Road object to the edge and calls the builder's
  // buildRoad function
  //@TODO shouldn't the pointer be a smart pointer?
  void buildRoad(Builder *builder);

  // return the edge number
  int getEdgeNum();
};

#endif // __EDGE_H_
