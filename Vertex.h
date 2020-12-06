#ifndef __VERTEX_H_
#define __VERTEX_H_

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class Residence;

class Vertex {
private:
  int number;
  shared_ptr<Residence> residence;
  vector<int> edges;

public:
  Vertex(int);

  int getVertexNum();

  shared_ptr<Residence> getResidence() { return residence; }

  friend class BoardModel;
};

#endif // __VERTEX_H_
