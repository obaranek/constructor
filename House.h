#ifndef _HOUSE_H_
#define _HOUSE_H_
#include "Residence.h"

class House: public Residence() {
  public:
    House();
    ~House() override;
};

#endif