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
  char getType();
  shared_ptr<Builder> getOwner();
  int getReward();
  char improveResidence();
};

#endif // __RESIDENCE_H_
