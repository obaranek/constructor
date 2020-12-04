#ifndef __VERTEX_H_
#define __VERTEX_H_

#include <memory>
#include <vector>

class Residence;

class Vertex {
private:
  int number;
  std::unique_ptr<Residence> residence;
  std::vector<int> edges;

public:
  Vertex(int);
  int getVertexNum();
};

#endif // __VERTEX_H_
