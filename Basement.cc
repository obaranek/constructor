#include "Map"
#include "Residence.h"
#include "Basement.h"
#include "ResourceType.h"

Basement::Basement(std::shared_ptr<Builder> _owner) 
    : reward{ 1 },
      type{ 'B' },
      owner{ _owner };
{
    // create cost map
    std::Map<ResourceType, int> basementMapCost;
    basementMapCost[ResourceType::BRICK] = 1;
    basementMapCost[ResourceType::ENERGY] = 1;   
    basementMapCost[ResourceType::GLASS] = 1;   
    basementMapCost[ResourceType::WIFI] = 1;

    cost{ basementMapCost };
}

Basement::~Basement() {}