#include "Vertex.h"
#include "Residence.h"
#include "Builder.h"

using namespace std;


Vertex::Vertex(int number) : vertexNumber{number} {};

void Vertex::buildResidence(shared_ptr<Builder> currBuilder){
  residence = make_shared<Residence>(currBuilder);
  currBuilder->buildResidence(vertexNumber);
}

void Vertex::improveResidence(shared_ptr<Builder> currBuilder){
  if( !(currBuilder->haveResidence(vertexNumber)) ){
    //@TODO: Throw exception- currBuilder doesn't have residence built
  }

  try{
    char newResType = residence->improveResidence();
    currBuilder->updateResidence(vertexNumber, newResType);
  }catch(...){
    //@TODO: Throw exception-
  }

}

int Vertex::getVertexNum() { return vertexNumber; }

shared_ptr<Residence> Vertex::getResidence() { return residence; }
