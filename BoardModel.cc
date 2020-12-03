#include "BoardModel.h"
#include "Edge.h"
#include "Vertex.h"
#include <fstream>
#include <sstream>

void BoardModel::init() {
  // reset state
  edges.clear();
  vertices.clear();
  tiles.clear();

  std::ifstream verticiesFile{"vertices.txt"};
  std::string line;

  // creating a vector of all the tiles
  for (int i = 0; i < 19; i++) { //
    tiles.emplace_back(i);
  }

  // creating a vector of all the vertices
  for (int i = 0; i < 54; i++) { //
    vertices.emplace_back(i);
  }

  // creating a vector of all the edges
  for (int i = 0; i < 72; i++) { //
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
    int tileNum = stoi(str);
    while (ss >> str) {
      int vertexNum = stoi(str);
      //@TODO: check with dhruv
      tiles.at(tileNum)->vertices.emplace_back(vertexNum);
    }
  }

  // initializing edges neighbouring each tile
  std::ifstream tileEdgesFile{"tile_edges.txt"};
  while (std::getline(tileVerticesFile, line)) {
    std::stringstream ss;
    ss << line;
    std::string str;
    int tileNum = stoi(str);
    while (ss >> str) {
      int edgeNum = stoi(str);
      //@TODO: check with dhruv
      tiles.at(tileNum)->edges.emplace_back(edgeNum);
    }
  }
}
