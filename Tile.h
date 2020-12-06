#ifndef __TILE_H_
#define __TILE_H_

#include "ResourceType.h"
#include <vector>

class Tile {
private:
  int tileNumber;
  ResourceType resourceType;
  int value;
  bool hasGeese;
  //@TODO reflect changes in UML
  std::vector<int> vertices;
  std::vector<int> edges;

public:
  int getTileNum();
};

#endif // __TILE_H_