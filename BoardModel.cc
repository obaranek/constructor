#ifndef BOARDMODEL_CC
#define BOARDMODEL_CC

#include "BoardModel.h"
#include "BoardView.h"
#include "Builder.h"
#include "Edge.h"
#include "Residence.h"
#include "Tile.h"
#include "Vertex.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <iostream>

using std::default_random_engine;
using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::istringstream;
using std::logic_error;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;

/***** Constructors *****/

BoardModel::BoardModel()
    : seed{-1}, theBoardView{std::make_unique<BoardView>()} {
  // make 4 builders:
  builders.emplace_back(std::make_shared<Builder>(Colour::BLUE));
  builders.emplace_back(std::make_shared<Builder>(Colour::RED));
  builders.emplace_back(std::make_shared<Builder>(Colour::ORANGE));
  builders.emplace_back(std::make_shared<Builder>(Colour::YELLOW));
  currBuilder = builders.at(0);
}

/***** Functions *****/

void BoardModel::prepareBoard() {
  // reset state
  edges.clear();
  vertices.clear();
  tiles.clear();

  // creating a vector of all the tiles
  for (int i = 0; i < 19; i++) {
    tiles.emplace_back(std::make_shared<Tile>(i));
  }

  // creating a vector of all the vertices
  for (int i = 0; i < 54; i++) {
    vertices.emplace_back(std::make_shared<Vertex>(i));
  }

  // creating a vector of all the edges
  for (int i = 0; i < 72; i++) {
    edges.emplace_back(std::make_shared<Edge>(i));
  }

  ifstream ifs;
  ifs.open("vertices.txt");
  if (ifs.fail()) {
    throw logic_error("BoardModel::init cannot open vertices.txt");
  }
  string line;
  stringstream iss;
  // initializing edges' and vertices' neighbours
  while (getline(ifs, line)) {
    iss << line;
    string word;
    iss >> word;
    int vertexNum = stoi(word);
    // adding adjacent vertices and edges to each other
    while (iss >> word) {
      int edgeNum = stoi(word);
      vertices.at(vertexNum)->edges.emplace_back(edgeNum);
      edges.at(edgeNum)->vertices.emplace_back(vertexNum);
    }
    iss.clear();
  }
  ifs.close();

  ifs.open("tiles_vertices.txt");
  if (ifs.fail()) {
    throw logic_error("BoardModel::init cannot open tile_vertices.txt");
  }

  // initializing vertices neighbouring each tile
  while (getline(ifs, line)) {
    iss << line;
    string word;
    iss >> word;
    int tileNum = stoi(word);
    while (iss >> word) {
      int vertexNum = stoi(word);
      tiles.at(tileNum)->vertices.emplace_back(vertexNum);
    }
    iss.clear();
  }
  ifs.close();

  // initializing edges neighbouring each tile
  while (getline(ifs, line)) {
    iss << line;
    string str;
    iss >> str;
    int tileNum = stoi(str);
    while (iss >> str) {
      int edgeNum = stoi(str);
      tiles.at(tileNum)->edges.emplace_back(edgeNum);
    }
    iss.clear();
  }
  ifs.close();

  // initializing the adjacent vertices for each vertex
  ifs.open("adjacentVertices.txt");
  if (ifs.fail()) {
    throw logic_error("BoardModel::init cannot open adjacentVertices");
  }

  while (getline(ifs, line)) {
    iss << line;
    string word;
    iss >> word;
    int vertexNum = stoi(word);
    while (iss >> word) {
      int adjacentVertexNum = stoi(word);
      vertices.at(vertexNum)->adjacentVertices.push_back(adjacentVertexNum);
    }
    iss.clear();
  }
  ifs.close();

  // initializing the adjacent vertices for each vertex
  ifs.open("adjacentEdges.txt");
  if (ifs.fail()) {
    throw logic_error("BoardModel::init cannot open adjacentedges file");
  }

  while (getline(ifs, line)) {
    iss << line;
    string word;
    iss >> word;
    int edgeNum = stoi(word);
    while (iss >> word) {
      int adjacentEdgeNum = stoi(word);
      edges.at(edgeNum)->adjacentEdges.push_back(adjacentEdgeNum);
    }
    iss.clear();
  }
  ifs.close();
}

void BoardModel::initBoard(string fileName) {
  prepareBoard();

  ifstream ifs{fileName};
  if (ifs.fail()) {
    throw logic_error("BoardModel::initBoard cannot open the layout file");
  }
  string line;
  getline(ifs, line);
  loadLayout(line, false);
}

void BoardModel::initLoad(std::string fileName) {
  
  prepareBoard();
  ifstream ifs{fileName};
  if (ifs.fail()) {
    throw logic_error("BoardModel::initLoad cannot open the load file");
  }
  int lineCtr = 1;
  string line;
  while (getline(ifs, line) && lineCtr <= 7) {
	  stringstream ss{line};
    if (lineCtr == 1) {
      int builderNum;
      ss >> builderNum;
      currBuilder = builders[builderNum];
    } else if (lineCtr >= 2 && lineCtr <= 5) {
	    loadBuilder(line, lineCtr - 2);
    } else if (lineCtr == 6) {
      loadLayout(line, true);
    } else if (lineCtr == 7) {
      int tile;
      ss >> tile;
      gooseTile = tiles.at(tile);
    }
    lineCtr++;
  }
}

void BoardModel::loadBuilder(string line, int builderNum) {
	stringstream ss{line};

  int tokenCtr = 0;
  std::string token;
  while (ss >> token) {
    if (tokenCtr >= 0 && tokenCtr <= 4) {
      int tokenNum = stoi(token);
      builders.at(builderNum)->takeResources(static_cast<ResourceType>(tokenCtr), tokenNum);
    } else if (token == "r") {
      string temp;
      while (ss >> temp && temp != "h") {
        int edgeNum = stoi(temp);
        edges.at(edgeNum)->buildRoad(builders.at(builderNum), true);
      }
      if (temp == "h") {
        int vertexNumber;
        char residenceType;
        while (ss >> vertexNumber) {
          ss >> residenceType;
          vertices.at(vertexNumber)->buildResidence(builders.at(builderNum), residenceType, true);
        }
      }
    }
    tokenCtr++;
  }
}

void BoardModel::loadLayout(std::string line, bool isLoad) {
  int tileNum = 0;
  int tileValue = 0;
  int resourceNum = 0;

  istringstream ss{line};

  while (ss >> resourceNum) {
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
      tiles.at(tileNum)->resourceType = PARK;
      if (!isLoad) {
        gooseTile = tiles.at(tileNum);
      }
      break;
    default:
      throw std::invalid_argument("BoardModel::loadLayout: Invalid Resource "
                                  "Type, Check you layout file");
    }
    ss >> tileValue;
    tiles.at(tileNum)->value = tileValue;
    tileNum++;
  }
}

void BoardModel::moveGeese(int tileNum) {
  gooseTile = tiles.at(tileNum);
  // Lmao this wasn't trivial, i forgot about the stealing bs
}

void BoardModel::buildResidence(int vertexNum, bool gameStart) {

  if(vertexNum < 0 || vertexNum > 53){
    throw invalid_argument("Sorry, that vertex does not exist. Please enter a different vertex number");
  }

  std::shared_ptr<Vertex> currVertex = vertices.at(vertexNum);
  
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
    throw logic_error("Building exists in adjacent vertex");
  }
  
  if (!gameStart) {

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
      throw logic_error(
          "You don't have a connecting road to build a residence");
    }
  }

  try{
    currVertex->buildResidence(currBuilder, 'B', gameStart);
  } catch(logic_error e){
    throw e;
  }
}

void BoardModel::improveResidence(int vertexNum) {
  if(vertexNum < 0 || vertexNum > 53){
    throw invalid_argument("That vertex does not exist, please enter another vertex number");
  }

  try{
    vertices.at(vertexNum)->improveResidence(currBuilder);
  } catch(logic_error e){
    throw e;
  }
}

void BoardModel::obtainResources(int value) {
  if (value == 7 || value > 12 || value < 2) {
    throw logic_error("BoardMdodel::obtainResources: Invalid value");
  }
  for (auto &tile : tiles) {
    if (tile->value == value) {
      ResourceType tileResource = tile->resourceType;
      for (auto &tileVertexNum : tile->vertices) {
        auto tileVertex = vertices.at(tileVertexNum);
        auto residence = tileVertex->getResidence();
        if (!residence) {
          continue;
        }
        int reward = residence->getReward();
        residence->getOwner()->takeResources(tileResource, reward);
      }
    }
  }
}

void BoardModel::BuildRoad(int edgeNum) {
  try{
    edges.at(edgeNum)->buildRoad(currBuilder);
  }catch(logic_error e){
    throw e;
  }
}

int BoardModel::rollDice() {
  vector<int> diceOptions = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // set the correct seed based on if flag is used or not
  unsigned long int localSeed;
  if (seed < 0) {
    localSeed = std::chrono::system_clock::now().time_since_epoch().count();
  } else {
    localSeed = seed;
  }

  // defining random number generator with correct seed
  default_random_engine rng{localSeed};
  // shuffling the dice option vector
  shuffle(diceOptions.begin(), diceOptions.end(), rng);
  // return a shuffled element from the dice options array
  return *(diceOptions.begin());
}

void BoardModel::playRoll(int diceValue) {
  if (diceValue == 7 || diceValue > 12 || diceValue < 2) {
    throw invalid_argument("BoardModel::obtainResources:: Invalid value");
  }
  // diceValue == 7 ? playGoose() : obtainResources(diceValue);
  obtainResources(diceValue); //@TODO: remove this once we implement goose
}

void BoardModel::next() {
  auto currBuilderIt = find(builders.begin(), builders.end(), currBuilder);

  if (currBuilderIt ==
      builders.end()) { // buider not found (should never happen)
    throw logic_error("Builder not found when incrementing");
  }

  // increment the currBuilder
  if (currBuilderIt + 1 == builders.end()) { // if we are at last builder
    currBuilder = *(builders.begin());
  } else { // there is a builder ahead (not at last builder)
    currBuilder = *(currBuilderIt + 1);
  }
}

void BoardModel::prevBuilder() {
  auto currBuilderIt = find(builders.begin(), builders.end(), currBuilder);

  if (currBuilderIt ==
      builders.end()) { // buider not found (should never happen)
    throw logic_error("Builder not found when decrementing");
  }

  // decrementing the currBuilder
  if (currBuilderIt == builders.begin()) { // if we are at the first builder
    currBuilder = *(builders.end() - 1);
  } else { // there is a builder infront of us (not at first builder)
    currBuilder = *(currBuilderIt - 1);
  }
}

bool BoardModel::checkWinner() {
  for (auto &builder : builders) {
    if (builder->getPoints() >= 10) {
      return true;
    }
  }
  return false;
}

/***** Print Functions *****/

void BoardModel::printBoard() { theBoardView->printBoard(this); }

void BoardModel::printResidences() {
  theBoardView->printResidence(currBuilder);
}

void BoardModel::printCurrBuilderTurn() {
  theBoardView->printCurrBuilderTurn(currBuilder);
}

void BoardModel::printStatus() { theBoardView->printStatus(builders); }

void BoardModel::beginGameHelp() { theBoardView->beginGameHelp(); }

void BoardModel::duringGameHelp() { theBoardView->duringGameHelp(); }

void BoardModel::printTradeResources(const Colour otherBuilder,
                                     const ResourceType give,
                                     const ResourceType take) {

  theBoardView->printTradeResource(currBuilder->getColour(), otherBuilder, give,
                                   take);
}

void BoardModel::printWhereBuild() {
  theBoardView->printWhereBuild(currBuilder->getColour());
}

/***** Getters and Setters *****/

shared_ptr<Builder> BoardModel::getCurrBuilder() { return currBuilder; }

shared_ptr<Vertex> BoardModel::getVertexPtr(int vertexNum) {
  return vertices.at(vertexNum);
}

shared_ptr<Tile> BoardModel::getTilePtr(int tileNum) {
  return tiles.at(tileNum);
}

std::shared_ptr<Edge> BoardModel::getEdgePtr(int edgeNum) {
  return edges.at(edgeNum);
}

char BoardModel::getDiceType() { return currBuilder->getDiceType(); }

std::shared_ptr<Tile> BoardModel::getGooseTile() { return gooseTile; }

void BoardModel::setDice(char type) {
  if (type == 'L' || type == 'F') {
    currBuilder->setDice(type);
  } else {
    throw invalid_argument("dice can only be of type L or F");
  }
}

void BoardModel::setSeed(int _seed) {
  if (_seed >= 0) {
    seed = _seed;
  } else {
    throw invalid_argument("seed can't be negative");
  }
}

#endif /* BOARDMODEL_CC */
