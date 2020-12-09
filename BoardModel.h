#ifndef __BOARDMODEL_H_
#define __BOARDMODEL_H_

#include "Colour.h"
#include "ResourceType.h"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

class Tile;
class Vertex;
class Builder;
class Edge;
class BoardView;

class BoardModel {
private:
  std::vector<std::shared_ptr<Tile>> tiles;
  std::shared_ptr<Tile> gooseTile;
  std::vector<std::shared_ptr<Vertex>> vertices;
  std::vector<std::shared_ptr<Edge>> edges;
  std::vector<std::shared_ptr<Builder>> builders;
  std::shared_ptr<Builder> currBuilder;
  std::unique_ptr<BoardView> theBoardView;
  int seed;

public:
  // default constructor sets seed to be 0
  BoardModel();

  void initBoard(std::string fileName = "layout.txt");

  // loadLayout() sets up the board according to the given text file
  void loadLayout(std::ifstream &, std::string fileName = "layout.txt");

  // moveGeese() sets gooseTile to point at tile of tileNum
  void moveGeese(int tileNum);

  // buildResidence() builds a residence on the given vertexNum
  void buildResidence(int vertexNum, bool gameStart);

  // improveResidence() delegates improving residence to Vertex
  void improveResidence(int vertexNum);

  // send the apropriate resources to all the builder who own a residence on the
  // tile with the given value
  void obtainResources(int value);

  // builds a road on the given edge number
  void BuildRoad(int);

  // returns a random number between 2 and 12 inclusives
  int rollDice();

  // decides how to proceede with roll after the dice has been rolled
  void playRoll(int);

  // next() increments the currBuilder to the next one
  void next();

  // prevBuilder() decrements the currBuilder to the prev one
  void prevBuilder();

  // returns true if a builder won the game
  bool checkWinner();

  /***** Print Functions *****/

  void printBoard();

  void printResidences();

  void printCurrBuilderTurn();

  void printStatus();

  void beginGameHelp();

  void duringGameHelp();

  void printTradeResources(const Colour otherBuilder, const ResourceType give,
                           const ResourceType take);

  void printWhereBuild();

  /***** Getters and Setters *****/

  std::shared_ptr<Builder> getCurrBuilder();
  char getDiceType();
  std::shared_ptr<Vertex> getVertexPtr(int);
  std::shared_ptr<Edge> getEdgePtr(int);
  std::shared_ptr<Tile> getTilePtr(int);

  void setDice(char type);
  void setSeed(int _seed);
};

#endif // __BOARDMODEL_H_
