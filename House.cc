#include "Map"
#include "Residence.h"
#include "House.h"
#include "ResourceType.h"

House::House(std::shared_ptr<Builder> _owner) 
    : reward{ 2 },
      type{ 'H' },
      owner{ _owner };
{
    // create cost map
    std::Map<ResourceType, int> houseMapCost;
    houseMapCost[ResourceType::GLASS] = 2;
    houseMapCost[ResourceType::HEAT] = 3;   

    cost{ houseMapCost };
}

House::~House() {}