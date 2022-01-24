#include "../include/Vertex.h"
#include "../include/Builder.h"
#include "../include/Residence.h"

#include <stdexcept>

using namespace std;
using std::invalid_argument;

Vertex::Vertex(int number) : vertexNumber{number} {};

void Vertex::buildResidence(shared_ptr<Builder> currBuilder, char residenceType,
                            bool gameStart) {

  // Check if no building exists on the vertex
  if (residence != NULL) {
    throw invalid_argument("Building already exists at that vertex");
  }

  if (!gameStart) {
    // Check if builder has enough resources
    bool enoughResources =
        currBuilder->checkResources({{BRICK, 1}, {ENERGY, 1}, {GLASS, 1}});
    if (!enoughResources) {
      throw logic_error("You don't have enough resources");
    }
  }

  residence = make_shared<Residence>(currBuilder, residenceType);
  std::map<ResourceType, int> cost = residence->getCost();
  currBuilder->buildResidence(vertexNumber, residenceType, cost, gameStart);
}

void Vertex::improveResidence(shared_ptr<Builder> currBuilder) {

  if (!(currBuilder->haveResidence(vertexNumber))) {
    throw invalid_argument("You do not own a residence at this vertex number");
  }

  try {
    residence->improveResidence(vertexNumber);
  } catch (logic_error &e) {
    throw e;
  }
}

int Vertex::getVertexNum() { return vertexNumber; }

shared_ptr<Residence> Vertex::getResidence() { return residence; }

vector<int> Vertex::getEdges() { return edges; }
