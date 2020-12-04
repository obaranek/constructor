#ifndef _BASEMENT_H_
#define _BASEMENT_H_
#include <Memory>
#include "Residence.h"
#include "Builder.h"

class Basement: public Residence() {
  public:
    Basement(std::shared_ptr<Builder> owner);
    ~Basement() override;
};

#endif