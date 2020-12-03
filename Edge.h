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
  Edge(int, Road *);
  friend class BoardModel;
};

#endif // __EDGE_H_
