#ifndef __VERTEX_H_
#define __VERTEX_H_

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class Residence;
class Builder;

class Vertex {
private:
  int vertexNumber;
  shared_ptr<Residence> residence;
  vector<int> edges;
  vector<int> adjacentVertices;

public:
  Vertex(int);

  void buildResidence(shared_ptr<Builder> currBuilder, char residenceType,
                      bool free);

  void improveResidence(shared_ptr<Builder> currBuilder);

  int getVertexNum();

  vector<int> getEdges();
  shared_ptr<Residence> getResidence();

  friend class BoardModel;
};

#endif // __VERTEX_H_
