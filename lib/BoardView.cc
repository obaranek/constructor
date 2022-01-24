#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../include/BoardModel.h"
#include "../include/Builder.h"
#include "../include/Colour.h"
#include "../include/Edge.h"
#include "../include/Residence.h"
#include "../include/ResourceType.h"
#include "../include/Tile.h"
#include "../include/Vertex.h"

using std::cout;
using std::endl;

// takes in a colour and returns the string equivalent of the colour
std::string colourReturn(Colour buildercolour) {
  if (buildercolour == BLUE) {
    return "Blue";
  } else if (buildercolour == RED) {
    return "Red";
  } else if (buildercolour == ORANGE) {
    return "Orange";
  } else {
    return "Yellow";
  }
}

// takes in a resourcetype and returns the string equivalent of the resource
std::string resourceReturn(ResourceType resource) {
  if (resource == ResourceType::BRICK) {
    return "brick";
  } else if (resource == ResourceType::ENERGY) {
    return "energy";
  } else if (resource == ResourceType::GLASS) {
    return "glass";
  } else if (resource == ResourceType::HEAT) {
    return "heat";
  } else {
    return "wifi";
  }
}

// Takes in a ResourceType and maps it to a string.
std::string resToString(ResourceType res) {
  switch (res) {
  case 0:
    return "BRICK";
  case 1:
    return "ENERGY";
  case 2:
    return "GLASS";
  case 3:
    return "HEAT";
  case 4:
    return "WIFI";
  case 5:
    return "PARK";
  default:
    return "ERROR"; // Print error if a diff resType is given
  }
}

// Returns a char with the first letter of builder colour
char getBuilderInitials(Colour col) {
  switch (col) {
  case 0:
    return 'B';
  case 1:
    return 'R';
  case 2:
    return 'O';
  case 3:
    return 'Y';
  default:
    return 'E'; // Incorrect ResourceType passed in
  }
}

// Returns a string with freq spaces
std::string BoardView::makeBlank(int freq) {
  std::string ans;

  for (int i = 0; i < freq; i++) {
    ans += " ";
  }

  return ans;
}

// Returns a string with housing or vertex num

std::string BoardView::printVertex(std::shared_ptr<Vertex> vertex) {

  auto resPtr = vertex->getResidence();
  int vertexNum = vertex->getVertexNum();

  std::string ans = "";

  if (resPtr != NULL) {
    char houseType = resPtr->getType();
    char colourInitials = getBuilderInitials(resPtr->getOwner()->getColour());
    ans += colourInitials;
    ans += houseType;
  } else {
    vertexNum < 10 ? ans = ans + " " + std::to_string(vertexNum)
                   : ans += std::to_string(vertexNum);
  }

  return ans;
}

// Returns a string with road or edge number
std::string BoardView::printEdge(std::shared_ptr<Edge> edge) {

  char hasRoad = edge->doesHaveRoad();
  int edgeNum = edge->getEdgeNum();

  std::string ans = "";

  if (hasRoad) {
    char colourInitials = getBuilderInitials(edge->getOwnerColour());
    ans = ans + colourInitials + "R";
  } else {
    edgeNum < 10 ? ans = ans + " " + std::to_string(edgeNum)
                 : ans += std::to_string(edgeNum);
  }

  return ans;
}

std::ostream &BoardView::edgeTileNumEdge(
    std::ostream &os, bool blank, const std::shared_ptr<Edge> leftEdge,
    const std::shared_ptr<Tile> tile, const std::shared_ptr<Edge> rightEdge) {

  if (blank) {
    os << makeBlank(10);
    return os;
  }

  int tileNum = -1;
  if (tile != NULL) {
    tileNum = tile->getTileNum();
  }

  if (leftEdge != NULL) {
    os << " " << printEdge(leftEdge) << " ";
  }

  os << makeBlank(2);

  if (tileNum >= 0) {
    tileNum < 10 ? os << " " << tileNum : os << tileNum;
  } else {
    os << makeBlank(2);
  }

  os << makeBlank(2);

  if (rightEdge != NULL) {
    os << " " << printEdge(rightEdge) << " ";
  }

  return os;
}

std::ostream &
BoardView::vertexEdgeVertex(std::ostream &os, bool blank,
                            const std::shared_ptr<Vertex> leftVertex,
                            const std::shared_ptr<Edge> edge,
                            const std::shared_ptr<Vertex> rightVertex) {

  if (blank) {
    os << makeBlank(10);
    return os;
  }

  if (leftVertex != NULL) {
    os << "|" << printVertex(leftVertex) << "|";
  }

  os << "--";
  if (edge != NULL) {
    os << printEdge(edge);
  }
  os << "--";

  if (rightVertex != NULL) {
    os << "|" << printVertex(rightVertex) << "|";
  }

  return os;
}

std::ostream &BoardView::borderResourceBorder(std::ostream &os, bool blank,
    const std::shared_ptr<Tile> tile, bool leftBar, bool rightBar,
    bool checkGeese, BoardModel* board) {

  std::string middle = "";

  if (blank) {
    os << makeBlank(10);
    return os;
  }

  if (leftBar) os << "  | ";

  if(!checkGeese){ // Printing ResourceType
    if (tile != NULL) {
      middle = resToString(tile->getResourceType());
    }

    if (middle.length() == 0) {
      os << makeBlank(6);
    } else {
      os << " " << middle;
    }
  }
  else{ // Printing Geese (if geese tile)
    if(tile == board->getGooseTile()){
      middle = "GEESE";
      os << " " << middle;
    } else {
      os << makeBlank(6);
    }
  }

  if (!rightBar) return os;

  switch(middle.length()){
    case 4:
      os << makeBlank(3);
      break;
    case 5:
      os << makeBlank(2);
      break;
    case 6:
      os << makeBlank(1);
      break;
    default:
      os << makeBlank(2);
      break;
  }

  os << "| ";
  return os;
}

std::ostream &BoardView::vertexTileValVertex(std::ostream &os,
                               const std::shared_ptr<Vertex> leftVertex,
                               const std::shared_ptr<Tile> tile,
                               const std::shared_ptr<Vertex> rightVertex) {

  if (leftVertex != NULL) {
    os << "|" << printVertex(leftVertex) << "|";
  }
  os << makeBlank(2);

  if (tile != NULL) {
    int tileVal = tile->getTileVal();
    ResourceType resType = tile->getResourceType();
    if (resType != ResourceType::PARK) {
      tileVal < 10 ? os << " " << tileVal : os << tileVal;
    } else {
      os << makeBlank(2);
    }
  } else {
    os << makeBlank(2);
  }
  os << makeBlank(2);

  if (rightVertex != NULL) {
    os << "|" << printVertex(rightVertex) << "|";
  }

  return os;
}

std::ostream &BoardView::printTileVal(std::ostream &os,
                                      const std::shared_ptr<Tile> tile) {

  int tileVal = -1;
  ResourceType resType = tile->getResourceType();

  if (tile != NULL) {
    tileVal = tile->getTileVal();
  }

  os << makeBlank(2);

  if (tileVal >= 0 && resType != ResourceType::PARK) {
    tileVal < 10 ? os << " " << tileVal : os << tileVal;
  } else {
    os << makeBlank(2);
  }

  os << makeBlank(2);
  return os;
}

// Prints the current status of all builders in order from builder 0 to 3
void BoardView::printStatus(
    const std::vector<std::shared_ptr<Builder>> &builderVector) {
  for (size_t counter = 0; counter < (builderVector.size()); ++counter) {
    std::shared_ptr<Builder> currentBuilder = builderVector.at(counter);
    std::map<ResourceType, int> resourceMap{currentBuilder->getResources()};

    // print the required output
    std::cout << colourReturn(currentBuilder->getColour()) << " has "
              << std::setw(5);
    std::cout << currentBuilder->getPoints() << " building points, ";
    std::cout << resourceMap[ResourceType::BRICK] << " brick, ";
    std::cout << resourceMap[ResourceType::ENERGY] << " energy, ";
    std::cout << resourceMap[ResourceType::GLASS] << " glass, ";
    std::cout << resourceMap[ResourceType::HEAT] << " heat, and ";
    std::cout << resourceMap[ResourceType::WIFI] << " WiFi." << std::endl;
  }
}

// Prints the residence owned by the builder
void BoardView::printResidence(const std::shared_ptr<Builder> builder) {
  // print <colour> has built
  std::cout << colourReturn(builder->getColour())
            << " has built: " << std::endl;

  // print all <vertex> <buildingType>
  std::map<int, char> buildingsMap{builder->getBuildings()};

  for (std::map<int, char>::iterator it = buildingsMap.begin();
       it != buildingsMap.end(); ++it) {
    std::cout << it->first << " " << it->second << std::endl;
  }
}

// Prints the current board
void BoardView::printBoard(BoardModel *board) {

  // Line 1:
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, false, board->getVertexPtr(0), board->getEdgePtr(0),
                   board->getVertexPtr(1));
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, true);
  cout << std::endl;

  // Line 2:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  cout << std::endl;

  // Line 3:
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, false, board->getEdgePtr(1), board->getTilePtr(0),
                  board->getEdgePtr(2));
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, true);
  cout << std::endl;

  // Line 4:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, board->getTilePtr(0), true, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  cout << std::endl;

  // Line 5:
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, false, board->getVertexPtr(2), board->getEdgePtr(3),
                   board->getVertexPtr(3));
  printTileVal(cout, board->getTilePtr(0));
  vertexEdgeVertex(cout, false, board->getVertexPtr(4), board->getEdgePtr(4),
                   board->getVertexPtr(5));
  vertexEdgeVertex(cout, true);
  cout << std::endl;

  // Line 6:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(0), false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, true);
  cout << std::endl;

  // Line 7:
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, false, board->getEdgePtr(5), board->getTilePtr(1),
                  board->getEdgePtr(6));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(7), board->getTilePtr(2),
                  board->getEdgePtr(8));
  edgeTileNumEdge(cout, false);
  cout << endl;

  // Line 8:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, board->getTilePtr(1), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(2), true, true);
  borderResourceBorder(cout, false);
  cout << endl;

  // Line 9:
  vertexEdgeVertex(cout, false, board->getVertexPtr(6), board->getEdgePtr(9),
                   board->getVertexPtr(7));
  printTileVal(cout, board->getTilePtr(1));
  vertexEdgeVertex(cout, false, board->getVertexPtr(8), board->getEdgePtr(10),
                   board->getVertexPtr(9));
  printTileVal(cout, board->getTilePtr(2));
  vertexEdgeVertex(cout, false, board->getVertexPtr(10), board->getEdgePtr(11),
                   board->getVertexPtr(11));
  cout << endl;

  // Line 10:
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(1),false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(2), false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  cout << std::endl;

  // Line 11:
  edgeTileNumEdge(cout, false, board->getEdgePtr(12), board->getTilePtr(3),
                  board->getEdgePtr(13));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(14), board->getTilePtr(4),
                  board->getEdgePtr(15));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(16), board->getTilePtr(5),
                  board->getEdgePtr(17));
  cout << endl;

  // Line 12:
  borderResourceBorder(cout, false, board->getTilePtr(3), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(4), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(5), true, true);
  cout << endl;

  // Line 13:
  vertexTileValVertex(cout, board->getVertexPtr(12), board->getTilePtr(3));
  vertexEdgeVertex(cout, false, board->getVertexPtr(13), board->getEdgePtr(18),
                   board->getVertexPtr(14));
  printTileVal(cout, board->getTilePtr(4));
  vertexEdgeVertex(cout, false, board->getVertexPtr(15), board->getEdgePtr(19),
                   board->getVertexPtr(16));
  vertexTileValVertex(cout, NULL, board->getTilePtr(5),
                      board->getVertexPtr(17));
  cout << endl;

  // Line 14:
  borderResourceBorder(cout, false, board->getTilePtr(3), true, true, true, board);
  borderResourceBorder(cout, false, NULL);
  borderResourceBorder(cout, false, board->getTilePtr(4), true, true, true, board);
  borderResourceBorder(cout, false, NULL, false, false);
  borderResourceBorder(cout, false, board->getTilePtr(5), true, true, true, board);
  cout << std::endl;

  // Line 15:
  edgeTileNumEdge(cout, false, board->getEdgePtr(20));
  edgeTileNumEdge(cout, false, board->getEdgePtr(21), board->getTilePtr(6),
                  board->getEdgePtr(22));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(23), board->getTilePtr(7),
                  board->getEdgePtr(24));
  edgeTileNumEdge(cout, false, NULL, NULL, board->getEdgePtr(25));
  cout << endl;

  // Line 16:
  borderResourceBorder(cout, false, NULL, true);
  borderResourceBorder(cout, false, board->getTilePtr(6), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(7), true, true);
  borderResourceBorder(cout, false, NULL, false, true);
  cout << endl;

  // Line 17:
  vertexEdgeVertex(cout, false, board->getVertexPtr(18), board->getEdgePtr(26),
                   board->getVertexPtr(19));
  printTileVal(cout, board->getTilePtr(6));
  vertexEdgeVertex(cout, false, board->getVertexPtr(20), board->getEdgePtr(27),
                   board->getVertexPtr(21));
  printTileVal(cout, board->getTilePtr(7));
  vertexEdgeVertex(cout, false, board->getVertexPtr(22), board->getEdgePtr(28),
                   board->getVertexPtr(23));
  cout << endl;

  // Line 18:
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(6),false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(7), false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  cout << std::endl;

  // Line 19:
  edgeTileNumEdge(cout, false, board->getEdgePtr(29), board->getTilePtr(8),
                  board->getEdgePtr(30));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(31), board->getTilePtr(9),
                  board->getEdgePtr(32));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(33), board->getTilePtr(10),
                  board->getEdgePtr(34));
  cout << endl;

  // Line 20:
  borderResourceBorder(cout, false, board->getTilePtr(8), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(9), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(10), true, true);
  cout << endl;

  // Line 21:
  vertexTileValVertex(cout, board->getVertexPtr(24), board->getTilePtr(8));
  vertexEdgeVertex(cout, false, board->getVertexPtr(25), board->getEdgePtr(35),
                   board->getVertexPtr(26));
  printTileVal(cout, board->getTilePtr(9));
  vertexEdgeVertex(cout, false, board->getVertexPtr(27), board->getEdgePtr(36),
                   board->getVertexPtr(28));
  vertexTileValVertex(cout, NULL, board->getTilePtr(10),
                      board->getVertexPtr(29));
  cout << endl;

  // Line 22:
  borderResourceBorder(cout, false, board->getTilePtr(8), true, true, true, board);
  borderResourceBorder(cout, false, NULL);
  borderResourceBorder(cout, false, board->getTilePtr(9), true, true, true, board);
  borderResourceBorder(cout, false, NULL, false, false);
  borderResourceBorder(cout, false, board->getTilePtr(10), true, true, true, board);
  cout << std::endl;

  // Line 23:
  edgeTileNumEdge(cout, false, board->getEdgePtr(37));
  edgeTileNumEdge(cout, false, board->getEdgePtr(38), board->getTilePtr(11),
                  board->getEdgePtr(39));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(40), board->getTilePtr(12),
                  board->getEdgePtr(41));
  edgeTileNumEdge(cout, false, NULL, NULL, board->getEdgePtr(42));
  cout << endl;

  // Line 24:
  borderResourceBorder(cout, false, NULL, true);
  borderResourceBorder(cout, false, board->getTilePtr(11), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(12), true, true);
  borderResourceBorder(cout, false, NULL, false, true);
  cout << endl;

  // Line 25:
  vertexEdgeVertex(cout, false, board->getVertexPtr(30), board->getEdgePtr(43),
                   board->getVertexPtr(31));
  printTileVal(cout, board->getTilePtr(11));
  vertexEdgeVertex(cout, false, board->getVertexPtr(32), board->getEdgePtr(44),
                   board->getVertexPtr(33));
  printTileVal(cout, board->getTilePtr(12));
  vertexEdgeVertex(cout, false, board->getVertexPtr(34), board->getEdgePtr(45),
                   board->getVertexPtr(35));
  cout << endl;

  // Line 26:
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(11),false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, false, board->getTilePtr(12), false, false, true, board);
  borderResourceBorder(cout, false, NULL, true, true);
  cout << std::endl;

  // Line 27:
  edgeTileNumEdge(cout, false, board->getEdgePtr(46), board->getTilePtr(13),
                  board->getEdgePtr(47));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(48), board->getTilePtr(14),
                  board->getEdgePtr(49));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(50), board->getTilePtr(15),
                  board->getEdgePtr(51));
  cout << endl;

  // Line 28:
  borderResourceBorder(cout, false, board->getTilePtr(13), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(14), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(15), true, true);
  cout << endl;

  // Line 29:
  vertexTileValVertex(cout, board->getVertexPtr(36), board->getTilePtr(13));
  vertexEdgeVertex(cout, false, board->getVertexPtr(37), board->getEdgePtr(52),
                   board->getVertexPtr(38));
  printTileVal(cout, board->getTilePtr(14));
  vertexEdgeVertex(cout, false, board->getVertexPtr(39), board->getEdgePtr(53),
                   board->getVertexPtr(40));
  vertexTileValVertex(cout, NULL, board->getTilePtr(15),
                      board->getVertexPtr(41));
  cout << endl;

  // Line 30:
  borderResourceBorder(cout, false, board->getTilePtr(13), true, true, true, board);
  borderResourceBorder(cout, false, NULL);
  borderResourceBorder(cout, false, board->getTilePtr(14), true, true, true, board);
  borderResourceBorder(cout, false, NULL, false, false);
  borderResourceBorder(cout, false, board->getTilePtr(15), true, true, true, board);
  cout << std::endl;

  // Line 31:
  edgeTileNumEdge(cout, false, board->getEdgePtr(54));
  edgeTileNumEdge(cout, false, board->getEdgePtr(55), board->getTilePtr(16),
                  board->getEdgePtr(56));
  edgeTileNumEdge(cout, false);
  edgeTileNumEdge(cout, false, board->getEdgePtr(57), board->getTilePtr(17),
                  board->getEdgePtr(58));
  edgeTileNumEdge(cout, false, NULL, NULL, board->getEdgePtr(59));
  cout << endl;

  // Line 32:
  borderResourceBorder(cout, false, NULL, true);
  borderResourceBorder(cout, false, board->getTilePtr(16), true, true);
  borderResourceBorder(cout, false);
  borderResourceBorder(cout, false, board->getTilePtr(17), true, true);
  borderResourceBorder(cout, false, NULL, false, true);
  cout << endl;

  // Line 33:
  vertexEdgeVertex(cout, false, board->getVertexPtr(42), board->getEdgePtr(60),
                   board->getVertexPtr(43));
  printTileVal(cout, board->getTilePtr(16));
  vertexEdgeVertex(cout, false, board->getVertexPtr(44), board->getEdgePtr(61),
                   board->getVertexPtr(45));
  printTileVal(cout, board->getTilePtr(17));
  vertexEdgeVertex(cout, false, board->getVertexPtr(46), board->getEdgePtr(62),
                   board->getVertexPtr(47));
  cout << endl;

  // Line 34:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, board->getTilePtr(16), true, true, true, board);
  borderResourceBorder(cout, false, NULL, false, false);
  borderResourceBorder(cout, false, board->getTilePtr(17), true, true, true, board);
  borderResourceBorder(cout, true);
  cout << std::endl;

  // Line 35:
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, false, board->getEdgePtr(63));
  edgeTileNumEdge(cout, false, board->getEdgePtr(64), board->getTilePtr(18),
                  board->getEdgePtr(65));
  edgeTileNumEdge(cout, false, NULL, NULL, board->getEdgePtr(66));
  edgeTileNumEdge(cout, true);
  cout << endl;

  // Line 36:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, NULL, true);
  borderResourceBorder(cout, false, board->getTilePtr(18), true, true);
  borderResourceBorder(cout, false, NULL, false, true);
  borderResourceBorder(cout, true);
  cout << endl;

  // Line 37:
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, false, board->getVertexPtr(48), board->getEdgePtr(67),
                   board->getVertexPtr(49));
  printTileVal(cout, board->getTilePtr(18));
  vertexEdgeVertex(cout, false, board->getVertexPtr(50), board->getEdgePtr(68),
                   board->getVertexPtr(51));
  vertexEdgeVertex(cout, true);
  cout << endl;

  // Line 38:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, board->getTilePtr(18), true, true, true, board);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  cout << endl;

  // Line 39:
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, false, board->getEdgePtr(69), NULL,
                  board->getEdgePtr(70));
  edgeTileNumEdge(cout, true);
  edgeTileNumEdge(cout, true);
  cout << endl;

  // Line 40:
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, false, NULL, true, true);
  borderResourceBorder(cout, true);
  borderResourceBorder(cout, true);
  cout << std::endl;

  // Line 41:
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, false, board->getVertexPtr(52), board->getEdgePtr(71),
                   board->getVertexPtr(53));
  vertexEdgeVertex(cout, true);
  vertexEdgeVertex(cout, true);
  cout << endl;
}

// Print Current Builder's Turn
void BoardView::printCurrBuilderTurn(const std::shared_ptr<Builder> builder) {
  Colour builderColour{builder->getColour()};

  std::cout << "Builder " << colourReturn(builderColour) << "'s turn."
            << std::endl;
}

// prints the required output to display when a trade is proposed
void BoardView::printTradeResource(const Colour thisBuilder,
                                   const Colour otherBuilder,
                                   const ResourceType giveResource,
                                   const ResourceType takeResource) {
  std::cout << colourReturn(thisBuilder) << " offers "
            << colourReturn(otherBuilder) << " one "
            << resourceReturn(giveResource) << " for one "
            << resourceReturn(takeResource) << "." << std::endl;
  std::cout << "Does " << colourReturn(otherBuilder) << " accept this offer?"
            << std::endl;
}

void BoardView::printWhereBuild(const Colour thisBuilder) {
  std::cout << "Builder " << colourReturn(thisBuilder)
            << ", where do you want to build a basement?" << std::endl;
}

// prints out the list of commands for begin game setting
void BoardView::beginGameHelp() {
  std::cout << "Valid Commands:" << std::endl;
  std::cout << "~ load : changes current builder's dice type to 'loaded'"
            << std::endl;
  std::cout << "~ fair : changes current builder's dice type to 'fair'"
            << std::endl;
  std::cout << "~ roll : rolls the dice and distributes resources."
            << std::endl;
  std::cout << "~ status : prints the current status of all builders in order "
               "from builder 0 to 3."
            << std::endl;
  std::cout << "~ help : prints out the list of commands." << std::endl;
}

// prints out the list of commands for during game setting
void BoardView::duringGameHelp() {
  std::cout << "Valid Commands:" << std::endl;
  std::cout << "~ board : prints the current board." << std::endl;
  std::cout << "~ status : prints the current status of all builders in order "
               "from builder 0 to 3."
            << std::endl;
  std::cout << "~ residence : prints the residences the current builder has "
               "currently completed."
            << std::endl;
  std::cout << "~ build-road <edge#> : attempts to builds the road at <road#>."
            << std::endl;
  std::cout
      << "~ build-res <housing#> : attempts to builds a basement at <housing#>."
      << std::endl;
  std::cout << "~ improve <housing#> : attempts to improve the residence at "
               "<housing#>."
            << std::endl;
  std::cout << "~ trade <colour> <give> <take> : attempts to trade with "
               "builder <colour>, giving one resource of type <give> and "
               "receiving one resource of type <take>."
            << std::endl;
  std::cout << "~ next : passes control onto the next builder in the game."
            << std::endl;
  std::cout << "~ save <file> : saves the current game state to <file>."
            << std::endl;
  std::cout << "~ help : prints out the list of commands." << std::endl;
}
