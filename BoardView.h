#ifndef _BOARDVIEW_H_
#define _BOARDVIEW_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Builder.h"
#include "Colour.h"
#include "ResourceType.h"

class Tile;
class Vertex;
class Edge;
class BoardModel;

class BoardView {
private:
  // Returns a string with freq spaces
  std::string makeBlank(int freq);

  // Returns a string with house or vertex number
  std::string printVertex(std::shared_ptr<Vertex> vertex);

  // Returns a string with road or edge number
  std::string printEdge(std::shared_ptr<Edge> edge);

  std::ostream &edgeTileNumEdge(std::ostream &os, bool blank = false,
                                const std::shared_ptr<Edge> leftEdge = NULL,
                                const std::shared_ptr<Tile> tile = NULL,
                                const std::shared_ptr<Edge> rightEdge = NULL);

  std::ostream &
  vertexEdgeVertex(std::ostream &os, bool blank = false,
                   const std::shared_ptr<Vertex> leftVertex = NULL,
                   const std::shared_ptr<Edge> edge = NULL,
                   const std::shared_ptr<Vertex> rightVertex = NULL);

  std::ostream &borderResourceBorder(std::ostream &os, bool blank = false,
                                     const std::shared_ptr<Tile> tile = NULL,
                                     bool leftBar = false,
                                     bool rightBar = false,
                                     bool checkGeese = false);

  std::ostream &
  vertexTileValVertex(std::ostream &os,
                      const std::shared_ptr<Vertex> leftVertex = NULL,
                      const std::shared_ptr<Tile> tile = NULL,
                      const std::shared_ptr<Vertex> rightVertex = NULL);

  std::ostream &printTileVal(std::ostream &os,
                             const std::shared_ptr<Tile> tile = NULL);

  void print1BarSet(const std::shared_ptr<Tile> potentialGoose = NULL);

public:
  // Prints the current status of all builders in order from builder 0 to 3
  void
  printStatus(const std::vector<std::shared_ptr<Builder>> &builderVectorPtr);

  // Prints the residence owned by the builder
  void printResidence(const std::shared_ptr<Builder> builder);

  // Prints the current board
  void printBoard(BoardModel *board);

  // Print Current Builder's Turn
  void printCurrBuilderTurn(const std::shared_ptr<Builder> builder);

  // Prints the required output to display when a trade is proposed
  void printTradeResource(const Colour thisBuilder, const Colour otherBuilder,
                          const ResourceType giveResource,
                          const ResourceType takeResource);

  // Prints the required output of where to build the building at the start of
  // the game
  void printWhereBuild(const Colour thisBuilder);

  // Prints out the list of commands for begin game setting
  void beginGameHelp();

  // Prints out the list of commands for during game setting
  void duringGameHelp();
};

#endif
