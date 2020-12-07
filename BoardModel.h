#ifndef __BOARDMODEL_H_
#define __BOARDMODEL_H_

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

  // send the apropriate resources to all the builder who own a residence on the
  // tile with the given value
  void obtainResouces(int value);

  
  

  /***** Print Functions *****/
  
  void printBoard();

  void printResidences();

  void printCurrBuilderTurn();

  void printStatus();

  void beginGameHelp();

  void duringGameHelp();

  void printTradeResources(const Colour otherBuilder, const ResourceType give, 
      const ResourceType take);



  /***** Getters and Setters *****/

  std::shared_ptr<Builder> getCurrBuilder(); 

  char getDiceType();

  void setDice(char type);

};

#endif // __BOARDMODEL_H_
