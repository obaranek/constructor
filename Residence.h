#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_
#include <memory>
#include <map>
#include "ResourceType.h"
#include "Builder.h"

class Residence(){
    Map<ResourceType, int> cost;
    int reward;
    char type;
    std::shared_ptr<Builder> owner;
  
  public:
    virtual ~Residence() = 0;
};

#endif