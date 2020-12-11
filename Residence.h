#ifndef __RESIDENCE_H_
#define __RESIDENCE_H_

#include "ResourceType.h"

#include <map>
#include <memory>

using std::map;
using std::shared_ptr;

class Builder;

class Residence {

private:
  map<ResourceType, int> cost;
  int reward;
  char type;
  shared_ptr<Builder> owner;

public:
  Residence(std::shared_ptr<Builder> owner);
  Residence(shared_ptr<Builder> builderPtr, char type);
  char getType();
  shared_ptr<Builder> getOwner();
  int getReward();
  char improveResidence();
  map<ResourceType, int> getCost();
};

#endif // __RESIDENCE_H_
