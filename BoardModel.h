#ifndef __BOARDMODEL_H_
#define __BOARDMODEL_H_

#include <memory>
#include <string>
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
  
  // loadLayout() sets up the board according to the given text file
  void loadLayout(std::string fileName = "layout.txt");

  // moveGeese() sets gooseTile to point at tile of tileNum
  void moveGeese(int tileNum);

  // buildResidence() builds a residence on the given vertexNum
  void buildResidence(int vertexNum, bool turnStart);

  // improveResidence() delegates improving residence to Vertex
  void improveResidence(int vertexNum);
};

#endif // __BOARDMODEL_H_
