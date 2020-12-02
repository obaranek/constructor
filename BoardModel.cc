#include "BoardModel.h"
#include "Edge.h"
#include "Vertex.h"
#include <fstream>
#include <sstream>

void BoardModel::init() {
  edges.clear();
  vertices.clear();

  std::ifstream infile{"vertices.txt"};
  std::string line;

  while (std::getline(infile, line)) {

    // creating a vector of all the edges
    for (int i = 0; i < 72; i++) { //
      edges.emplace_back(i, nullptr);
    }

    std::stringstream ss;
    ss << line;
    std::string str;
    ss >> str;
    int vertexNum = stoi(str);
    vertices.emplace_back(vertexNum, nullptr);

    // adding adjacent vertices and edges to each other
    while (ss >> str) {
      int edgeNum = stoi(str);
      vertices.at(vertexNum)->edges.emplace_back(edgeNum);
      edges.at(edgeNum)->vertices.emplace_back(vertexNum);
    }
  }
}
