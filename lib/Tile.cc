#include "../include/Tile.h"

Tile::Tile(int tileNum) : tileNumber{tileNum}, hasGeese{false} {};

ResourceType Tile::getResourceType() { return resourceType; }

int Tile::getTileVal() { return value; }

int Tile::getTileNum() { return tileNumber; }
