#ifndef _TOWER_H_
#define _TOWER_H_
#include "Residence.h"

class Tower: public Residence() {
  public:
    Tower();
    ~Tower() override;
};

#endif