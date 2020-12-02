#ifndef __BOARDMODEL_H_
#define __BOARDMODEL_H_

#include <memory>
#include <vector>

class Tile;
class Vertex;
class Builder;
class Edge;

class BoardModel {
private:
  std::vector<std::shared_ptr<Tile>> tiles;
  std::shared_ptr<Tile> gooseTile;
  std::vector<std::shared_ptr<Vertex>> vertices;
  std::vector<std::shared_ptr<Edge>> edges;
  std::vector<std::shared_ptr<Builder>> builders;
  std::shared_ptr<Builder> currBuilder;

public:
  void init();
};

#endif // __BOARDMODEL_H_
