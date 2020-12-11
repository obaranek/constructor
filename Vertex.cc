#include "Vertex.h"
#include "Builder.h"
#include "Residence.h"

using namespace std;

Vertex::Vertex(int number) : vertexNumber{number} {};

void Vertex::buildResidence(shared_ptr<Builder> currBuilder) {
  residence = make_shared<Residence>(currBuilder);
  std::map<ResourceType, int> cost = residence->getCost();
  currBuilder->buildResidence(vertexNumber, 'B', cost);
}

void Vertex::buildResidence(shared_ptr<Builder> currBuilder,
                            char residenceType) {
  residence = make_shared<Residence>(currBuilder, residenceType);
  std::map<ResourceType, int> cost = residence->getCost();
  currBuilder->buildResidence(vertexNumber, residenceType, cost);
}

void Vertex::improveResidence(shared_ptr<Builder> currBuilder) {
  if (!(currBuilder->haveResidence(vertexNumber))) {
    //@TODO: Throw exception- currBuilder doesn't have residence built
  }

  try {
    char newResType = residence->improveResidence();
    currBuilder->updateResidence(vertexNumber, newResType);
  } catch (...) {
    //@TODO: Throw exception-
  }
}

int Vertex::getVertexNum() { return vertexNumber; }

shared_ptr<Residence> Vertex::getResidence() { return residence; }
