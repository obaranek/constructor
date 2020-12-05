#include "Map"
#include "Residence.h"
#include "Tower.h"
#include "ResourceType.h"

Tower::Tower(std::shared_ptr<Builder> _owner) 
    : reward{ 3 },
      type{ 'T' },
      owner{ _owner };
{
    // create cost map
    std::Map<ResourceType, int> towerMapCost;
    towerMapCost[ResourceType::BRICK] = 3;
    towerMapCost[ResourceType::ENERGY] = 2;
    towerMapCost[ResourceType::GLASS] = 2;
    towerMapCost[ResourceType::WIFI] = 1;
    towerMapCost[ResourceType::HEAT] = 2;

    cost{ towerMapCost };
}

Tower::~Tower() {}