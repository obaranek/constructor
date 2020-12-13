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
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

using std::default_random_engine;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::invalid_argument;
using std::istringstream;
using std::logic_error;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;
using std::map;

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
      gooseTile = tile;
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
      builders.at(builderNum)
          ->takeResources(static_cast<ResourceType>(tokenCtr), tokenNum);
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
          vertices.at(vertexNumber)
              ->buildResidence(builders.at(builderNum), residenceType, true);
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
        gooseTile = tileNum;
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

void BoardModel::buildResidence(int vertexNum, bool gameStart) {

  if (vertexNum < 0 || vertexNum > 53) {
    throw invalid_argument("Invalid <housing#>");
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

  try {
    currVertex->buildResidence(currBuilder, 'B', gameStart);
  } catch (logic_error e) {
    throw e;
  }
}

void BoardModel::improveResidence(int vertexNum) {
  if (vertexNum < 0 || vertexNum > 53) {
    throw invalid_argument("Invalid <housing#>");
  }

  try {
    vertices.at(vertexNum)->improveResidence(currBuilder);
  } catch (logic_error e) {
    throw e;
  }
}

void BoardModel::obtainResources(int value) {
  if (value > 12 || value < 2) {
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
  if (edgeNum < 0 || edgeNum > 71) {
    throw invalid_argument("Invalid <road#>");
  }

  try {
    edges.at(edgeNum)->buildRoad(currBuilder, false);
  } catch (logic_error e) {
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
  std::cout << "Random Dice Number: " << *(diceOptions.begin()) << std::endl;
  return *(diceOptions.begin());
}

void BoardModel::playRoll(int diceValue) {
  if (diceValue > 12 || diceValue < 2) {
    throw invalid_argument("BoardModel::obtainResources:: Invalid value");
  }
  if (diceValue == 7) {
    playGoose();
    theBoardView->printBoard(this);
  } else {
    obtainResources(diceValue);
  }
}

string getColourStr(Colour colour) {
  if (colour == BLUE) {
    return "Blue";
  } else if (colour == ORANGE) {
    return "Orange";
  } else if (colour == RED) {
    return "Red";
  }
  return "Yellow";
}

int getRndResource(int seed) {
  vector<int> diceOptions = {0, 1, 2, 3, 4};

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
  return *(diceOptions.begin());
}

int BoardModel::getStolenResource(std::shared_ptr<Builder> victim) {
  int totalResources = 0;
  for (auto el : victim->getResources()) {
    totalResources += el.second;
  }

  vector<int> resourceOptions = {};
  int numBrick = totalResources != 0 ? (victim->getResources()[BRICK] * 100) / totalResources : 0;
  int numEnergy = totalResources != 0 ? (victim->getResources()[ENERGY] * 100) / totalResources : 0;
  int numHeat = totalResources != 0 ? (victim->getResources()[HEAT] * 100) / totalResources : 0;
  int numWifi = totalResources != 0 ? (victim->getResources()[WIFI] * 100) / totalResources : 0;
  int numGlass = totalResources != 0 ? (victim->getResources()[GLASS] * 100) / totalResources : 0;

  for (int i = 0; i < numBrick; i++) {
    resourceOptions.push_back(static_cast<int>(BRICK));
  }
  for (int i = 0; i < numEnergy; i++) {
    resourceOptions.push_back(static_cast<int>(ENERGY));
  }
  for (int i = 0; i < numHeat; i++) {
    resourceOptions.push_back(static_cast<int>(HEAT));
  }
  for (int i = 0; i < numWifi; i++) {
    resourceOptions.push_back(static_cast<int>(WIFI));
  }
  for (int i = 0; i < numGlass; i++) {
    resourceOptions.push_back(static_cast<int>(GLASS));
  }

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
  shuffle(resourceOptions.begin(), resourceOptions.end(), rng);
  return *(resourceOptions.begin());
}

void BoardModel::playGoose() {
  for (auto &builder : builders) {
    map<ResourceType, int> resourcesLost = {
        {BRICK, 0}, {WIFI, 0}, {ENERGY, 0}, {GLASS, 0}, {HEAT, 0}};
    map<ResourceType, int> builderResources = builder->getResources();

    int totalResources = 0;
    for (auto el : builderResources) {
      totalResources += el.second;
    }

    int lostResources = totalResources / 2;
    for (int i = 0; i < lostResources; i++) {
      int resourceLost = getRndResource(seed);
      resourcesLost[static_cast<ResourceType>(resourceLost)] += 1;
      builderResources[static_cast<ResourceType>(resourceLost)] -= 1;
    }

    std::string color = "";
    Colour builderColour = builder->getColour();
    color = getColourStr(builderColour);
    std::cout << "Builder " << color << " loses " << lostResources
              << " resources to the geese . They lose: " << std::endl;

    for (auto &el : resourcesLost) {
      std::string resource = "";
      if (el.first == BRICK) {
        resource = "BRICK";
      } else if (el.first == WIFI) {
        resource = "WIFI";
      } else if (el.first == ENERGY) {
        resource = "ENERGY";
      } else if (el.first == GLASS) {
        resource = "GLASS";
      } else if (el.first == HEAT) {
        resource = "HEAT";
      }
      std::cout << el.second << " " << resource << std::endl;
    }
  }

  int newGooseTile = -1;
  bool isValidGooseTile = false;
  std::string tempGooseString;

  while (!isValidGooseTile) {
    std::cout << "Choose where to place the GEESE." << std::endl;
    std::cin >> tempGooseString;
    std::stringstream ss {tempGooseString};

    if ( ss >> newGooseTile && newGooseTile != gooseTile && newGooseTile >= 0 && newGooseTile <= 18 ) {
      isValidGooseTile = true;
    } else {
      std::cout << "Invalid goose Tile! Choose Again." << std::endl;
    }
  }
  gooseTile = newGooseTile;

  vector<shared_ptr<Builder>> stealFrom{};
  for (auto &vertexNum : tiles.at(gooseTile)->vertices) {
    if (vertices.at(vertexNum)->getResidence() == nullptr) {
      continue;
    } else if (vertices.at(vertexNum)->getResidence()->getOwner() ==
               currBuilder) {
      continue;
    }
    int totalBuilderResources = 0;
    for (auto &el: vertices.at(vertexNum)->getResidence()->getOwner()->getResources()) {
      totalBuilderResources += el.second;
    }
    auto currVertexOwner = vertices.at(vertexNum)->getResidence()->getOwner();
    if (currVertexOwner != nullptr && totalBuilderResources > 0) {
      stealFrom.push_back(currVertexOwner);
    }
  }

  if (stealFrom.size() > 0) {
    std::cout << "Builder " << getColourStr(currBuilder->getColour())
              << " can choose to steal from";
    for (auto it = stealFrom.begin(); it != stealFrom.end(); ++it) {
      std::cout << " " << getColourStr(it->get()->getColour());
      if (it == stealFrom.end() - 1) {
        std::cout << std::endl;
      } else {
        std::cout << ",";
      }
    }
    string answer = "";
    Colour victimColor;
    bool validColor = false;

    do {
     std::cout << "Choose a builder to steal from." << std::endl;
     std::cin >> answer;
      if (answer == "Blue") {
        victimColor = BLUE;
        validColor = true;
      } else if (answer == "Orange") {
        victimColor = ORANGE;
        validColor = true;
      } else if (answer == "Red") {
        victimColor = RED;
        validColor = true;
      } else if (answer == "Yellow") {
        victimColor = YELLOW;
        validColor = true;
      } else {
        std::cout << "Invalid colour, make sure you enter the color corretly(case-sensitive)" << std::endl;
      }
    } while (!validColor);

    shared_ptr<Builder> victim = builders.at(victimColor);
    ResourceType stolenResource =
        static_cast<ResourceType>(getStolenResource(victim));
    victim->takeResources(stolenResource, -1);
    currBuilder->takeResources(stolenResource, 1);
  } else {
    std::cout << "Builder " << getColourStr(currBuilder->getColour())
              << " has no builders to seal from." << std::endl;
  }
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

void BoardModel::tradeResource(Colour otherBuilder, ResourceType give,
                               ResourceType take) {
  shared_ptr<Builder> otherBuilderPtr = builders[otherBuilder];
  if (currBuilder->getResources()[give] > 0 &&
      otherBuilderPtr->getResources()[take] > 0) {
    currBuilder->getResources()[give] -= 1;
    otherBuilderPtr->getResources()[take] -= 1;
    currBuilder->getResources()[take] += 1;
    otherBuilderPtr->getResources()[give] += 1;
  } else {
    throw logic_error("BoardModel::tradeResource: Not enough resources");
  }
}

std::string BoardModel::makeBuilderDataString(shared_ptr<Builder> builderPtr){
  string dataString = "";

  // Resources
  map<ResourceType, int> & builderResources = builderPtr->getResources();
  dataString += std::to_string(builderResources[BRICK]);
  dataString += " ";
  dataString += std::to_string(builderResources[ENERGY]);
  dataString += " ";
  dataString += std::to_string(builderResources[GLASS]);
  dataString += " ";
  dataString += std::to_string(builderResources[HEAT]);
  dataString += " ";
  dataString += " ";
  dataString += std::to_string(builderResources[WIFI]);
  dataString += " ";

  // Roads
  dataString += "r ";
  vector<int>& builderRoads = builderPtr->getRoads();
  for(int road : builderRoads){
    dataString += std::to_string(road);
    dataString += " ";
  }

  // Residences
  dataString += "h ";
  map<int, char>& builderResidences = builderPtr->getBuildings();
  for(auto elem : builderResidences){
    dataString += std::to_string(elem.first);
    dataString += " ";
    dataString += elem.second;
    dataString += " ";
  }

  return dataString;
}

std::string BoardModel::makeBoardDataString(){

  std::string dataString = "";
  
  for(auto tile : tiles){
    ResourceType res = tile->getResourceType();
    dataString += std::to_string(res) + " ";
    int val = tile->getTileVal();
    dataString += std::to_string(val) + " ";
  }

  return dataString;
}


void BoardModel::save(std::string fileName){

  ofstream ofs{fileName};
  if(ofs.fail()){
    throw logic_error("Invalid filename passed to save");
  }

  // Store the currentBuilder's colour
  int currBuilderNumber = currBuilder->getColour();
  ofs << currBuilderNumber << std::endl;

  // Store Builders' data
  std::string builder0Data = makeBuilderDataString(builders[0]);
  std::string builder1Data = makeBuilderDataString(builders[1]);
  std::string builder2Data = makeBuilderDataString(builders[2]);
  std::string builder3Data = makeBuilderDataString(builders[3]);
  ofs << builder0Data << std::endl << builder1Data << std::endl
    << builder2Data << std::endl << builder3Data << std::endl;

  // Store board layout
  std::string boardData = makeBoardDataString();
  ofs << boardData << std::endl;

  // Store goose tile
  std::string gooseTileData = std::to_string(gooseTile);
  ofs << gooseTileData << std::endl;

  ofs.close();
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

std::shared_ptr<Tile> BoardModel::getGooseTile() { return tiles.at(gooseTile); }

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
