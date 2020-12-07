#include "Vertex.h"
#include "Residence.h"
#include "Builder.h"

using namespace std;


Vertex::Vertex(int number) : vertexNumber{number} {};

void Vertex::buildResidence(shared_ptr<Builder> currBuilder){
  residence = make_shared<Residence>(vertexNumber);
  currBuilder->buildResidence(vertexNumber);
}

int Vertex::getVertexNum() { return number; }
