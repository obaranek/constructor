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
  std::vector<int> vertices;
  std::vector<int> edges;

public:
  Tile(int);
  int getTileNum();
  ResourceType getResourceType();
  int getTileVal();

  friend class BoardModel;
};

#endif // __TILE_H_
