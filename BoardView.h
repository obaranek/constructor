#ifndef _BOARDVIEW_H_
#define _BOARDVIEW_H_
#include <vector>
#include <memory>
#include "Builder.h"
#include "ResourceType.h"
#include "BoardModel.h"
#include "Colour.h"


class BoardView() {
  public:
    // Prints the current status of all builders in order from builder 0 to 3
    void printStatus(const std::vector<std::shared_ptr<Builder>> & builderVectorPtr);

    // Prints the residence owned by the builder
    void printResidence(const std::shared_ptr<Builder> builder);

    // Prints the current board
    void printBoard(const std::shared_ptr<BoardModel> board);

    // Print Current Builder's Turn
    void printCurrBuilderTurn(const std::shared_ptr<Builder> builder);

    // Prints the required output to display when a trade is proposed
    void printTradeResource(const Colour thisBuilder, const Colour otherBuilder, const ResourceType giveResource, const ResourceType takeResource);

    // Prints the required output of where to build the building at the start of the game
    void printWhereBuild(const Colour thisBuilder);

    // Prints out the list of commands for begin game setting
    void beginGameHelp();

    // Prints out the list of commands for during game setting
    void duringGameHelp();
};

#endif
