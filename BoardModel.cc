#include "BoardModel.h"
#include "Edge.h"
#include "Residence.h"
#include "Tile.h"
#include "Vertex.h"
#include "BoardView.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::shared_ptr;
using std::string;
using std::stringstream;

void BoardModel::init() {
  // reset state
  edges.clear();
  vertices.clear();
  tiles.clear();

  std::ifstream verticiesFile{"vertices.txt"};
  string line;

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
  while (getline(verticiesFile, line)) {
    stringstream ss;
    ss << line;
    string str;
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
  ifstream tileVerticesFile{"tile_vertices.txt"};
  while (getline(tileVerticesFile, line)) {
    stringstream ss;
    ss << line;
    string str;
    ss >> str;
    int tileNum = stoi(str);
    while (ss >> str) {
      int vertexNum = stoi(str);
      tiles.at(tileNum)->vertices.emplace_back(vertexNum);
    }
  }

  // initializing edges neighbouring each tile
  ifstream tileEdgesFile{"tile_edges.txt"};
  while (getline(tileVerticesFile, line)) {
    stringstream ss;
    ss << line;
    string str;
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
  ifstream layoutFile{fileName};
  string line;
  int tileNum = 0;
  while (std::getline(layoutFile, line)) {
    stringstream ss;
    string str;
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
      throw std::invalid_argument("BoardModel::loadLayout: Invalid Resource "
                                  "Type, Check you layout file");
    }
    tiles.at(tileNum)->value = tileValue;
    tileNum++;
  }
}

void BoardModel::moveGeese(int tileNum) {
  gooseTile = tiles.at(tileNum);
  // Lmao this wasn't trivial, i forgot about the stealing bs
}

void BoardModel::buildResidence(int vertexNum, bool gameStart) {

  std::shared_ptr<Vertex> currVertex = vertices.at(vertexNum);

  std::map<ResourceType, int> requiredResources = {
    {ResourceType::BRICK, 1},
    {ResourceType::ENERGY, 1}, 
    {ResourceType::GLASS, 1}, 
    {ResourceType::WIFI, 1},
  };

  // Check if no building exists on the vertex
  if (currVertex->residence != NULL) {
    //@TODO: Throw exception- Building already exists at that vertex
  }

  // Check if any adjacent vertices already have a residence built
  bool adjacentResidence = false;

  for (auto vertexNumIt = currVertex->adjacentVertices.begin();
       vertexNumIt != currVertex->adjacentVertices.end(); vertexNumIt++) {
    int vertexNum = *vertexNumIt;

    if (vertices.at(vertexNum)->residence != NULL) {
      adjacentResidence = true;
      break;
    }
  }

  if (adjacentResidence) {
    //@TODO: Throw Exception- Building in adjacent vertex
  }


  if (!gameStart) {
    
    // Check if builder has enough resources
    bool enoughResources = currBuilder->checkResources(requiredResources);

    if (!enoughResources) {
      //@TODO: Throw exception- not enough resources
    }

    
    // Check if builder has a road connecting to vertex
    bool connectingRoad = false;

    for (auto edgeNumIt = currVertex->edges.begin();
         edgeNumIt != currVertex->edges.end(); edgeNumIt++) {
      int edgeNum = *edgeNumIt;
      auto ownerColour = edges.at(edgeNum)->getOwnerColour();

      if (ownerColour == currBuilder->getColour()) {
        connectingRoad = true;
        break;
      }
    }

    if (!connectingRoad) {
      //@TODO: Throw exception- Not start of turn && no connecting road
    }
  }

  // All conditions checked- Can build residence
  currVertex->buildResidence(currBuilder);
}

void BoardModel::improveResidence(int vertexNum) {
  vertices.at(vertexNum)->improveResidence(currBuilder);
}

void BoardModel::obtainResources(int value) {
  if (value == 7 || value > 12 || value < 2) {
    throw invalid_argument("BoardModel::obtainResources:: Invalid value");
  }

  for (auto &tile : tiles) {
    if (tile->value == value) {
      ResourceType tileResource = tile->resourceType;
      for (auto &tileVertexNum : tile->vertices) {
        auto tileVertex = vertices.at(tileVertexNum);
        //@TODO add getter for tile
        auto residence = tileVertex->getResidence();
        if (!residence) {
          break;
        }
        //@TODO add getter for residence
        int reward = residence->getReward();
        //@TODO add takeResources for Builder
        residence->getOwner()->takeResources(tileResource, reward);
      }
    }
  }
}

/***** Print Functions *****/

void BoardModel::printBoard() { theBoardView->printBoard(this); }

void BoardModel::printResidences() { theBoardView->printResidences(currBuilder); }

void BoardModel::printCurrBuilderTurn() { theBoardView->printCurrBuilderTurn(currBuilder); }

void BoardModel::printStatus() { theBoardView->printStatus(builders); }

void BoardModel::beginGameHelp() { theBoardView->beginGameHelp(); }

void BoardModel::duringGameHelp() { theBoardView->duringGameHelp(); }

void BoardModel::printTradeResources(const Colour otherBuilder, 
    const ResourceType give, const ResourceType take) {
  
  theBoardView->printTradeResources(
      currBuilder->getColour(), otherBuilder->getColour, give, take );
}


/***** Getters and Setters *****/

std::shared_ptr<Builder> BoardModel::getCurrBuilder() { return currBuilder; }

char BoardModel::getDiceType() { return currBuilder->getDiceType(); }

void BoardModel::setDice(char type) { currBuilder->setDice(type); }
