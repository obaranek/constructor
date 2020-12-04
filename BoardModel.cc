#include "BoardModel.h"
#include "Edge.h"
#include "Tile.h"
#include "Vertex.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

void BoardModel::init() {
  // reset state
  edges.clear();
  vertices.clear();
  tiles.clear();

  std::ifstream verticiesFile{"vertices.txt"};
  std::string line;

  // creating a vector of all the tiles
  for (int i = 0; i < 19; i++) {
    tiles.emplace_back(i);
  }

  // creating a vector of all the vertices
  for (int i = 0; i < 54; i++) {
    vertices.emplace_back(i);
  }

  // creating a vector of all the edges
  for (int i = 0; i < 72; i++) {
    edges.emplace_back(i);
  }

  // initializing edges' and vertices' neighbours
  while (std::getline(verticiesFile, line)) {
    std::stringstream ss;
    ss << line;
    std::string str;
    ss >> str;
    int vertexNum = stoi(str);
    // adding adjacent vertices and edges to each other
    while (ss >> str) {
      int edgeNum = stoi(str);
      vertices.at(vertexNum)->edges.emplace_back(edgeNum);
      edges.at(edgeNum)->vertices.emplace_back(vertexNum);
    }
  }

  // initializing vertices neighbouring each tile
  std::ifstream tileVerticesFile{"tile_vertices.txt"};
  while (std::getline(tileVerticesFile, line)) {
    std::stringstream ss;
    ss << line;
    std::string str;
    ss >> str;
    int tileNum = stoi(str);
    while (ss >> str) {
      int vertexNum = stoi(str);
      tiles.at(tileNum)->vertices.emplace_back(vertexNum);
    }
  }

  // initializing edges neighbouring each tile
  std::ifstream tileEdgesFile{"tile_edges.txt"};
  while (std::getline(tileVerticesFile, line)) {
    std::stringstream ss;
    ss << line;
    std::string str;
    ss >> str;
    int tileNum = stoi(str);
    while (ss >> str) {
      int edgeNum = stoi(str);
      tiles.at(tileNum)->edges.emplace_back(edgeNum);
    }
  }

  // loading layout from layout.txt
  loadLayout();
}

void BoardModel::loadLayout(std::string fileName) {
  std::ifstream layoutFile{fileName};
  std::string line;
  int tileNum = 0;
  while (std::getline(layoutFile, line)) {
    std::stringstream ss;
    std::string str;
    int tileValue;
    int resourceNum;
    ss >> str;
    resourceNum = stoi(str);
    ss >> str;
    tileValue = stoi(str);
    switch (resourceNum) {
    case BRICK:
      tiles.at(tileNum)->resourceType = BRICK;
      break;
    case ENERGY:
      tiles.at(tileNum)->resourceType = ENERGY;
      break;
    case GLASS:
      tiles.at(tileNum)->resourceType = GLASS;
      break;
    case HEAT:
      tiles.at(tileNum)->resourceType = HEAT;
      break;
    case WIFI:
      tiles.at(tileNum)->resourceType = WIFI;
      break;
    case PARK:
      break;
    default:
      throw std::invalid_argument(
          "Invalid Resource Type, Check you layout file");
    }
    tiles.at(tileNum)->value = tileValue;
    tileNum++;
  }
}
