#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iomanip>
#include "BoardModel.h"
#include "Builder.h"
#include "Colour.h"
#include "ResourceType.h"

// Prints the current status of all builders in order from builder 0 to 3
void BoardView::printStatus(const std::vector<std::shared_ptr<Builder>> & builderVectorPtr) {
    for (int counter = 0; counter < (*builderVectorPtr.size()); ++counter) {
        std::shared_ptr<Builder> currentBuilder{ *(builderVectorPtr[counter]) };
        std::map<ResourceType, int> resourceMap{ builder.getResource() };

        // print the required output
        std::cout << currentBuilder.getColour() << " has " << std::setw(5);
        std::cout << currentBuilder.getPoints() << " building points, ";
        std::cout << residenceMap[ResourceType::BRICK] << " brick, ";
        std::cout << residenceMap[ResourceType::ENERGY] << " energy, ";
        std::cout << residenceMap[ResourceType::GLASS] << " glass, ";
        std::cout << residenceMap[ResourceType::HEAT] << " heat, and ";
        std::cout << residenceMap[ResourceType::WIFI] << " WiFi." << std::endl;   
    }
}

// Prints the residence owned by the builder
void BoardView::printResidence(const std::shared_ptr<Builder> builder) {
    // print <color> has built
    std::cout << builder->getColor() << " has built: " << std::endl;
  
    //print all <vertex> <buildingType>
    std::map<int, char> buildingsMap{ builder->getBuildings() };

    for (std::map<int, char>::iterator it = buildingsMap.begin(); it != buildingsMap.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

// Prints the current board
void BoardView::printBoard(const std::shared_ptr<BoardModel> board) {

}

// Print Current Builder's Turn
void printCurrBuilderTurn(const std::shared_ptr<Builder> builder) {
    std::cout << "Builder " << builder->getColour() << "'s turn." << std::endl;
}

// prints the required output to display when a trade is proposed
void printTradeResource(const Colour thisBuilder, const Colour otherBuilder, const ResourceType giveResource, const ResourceType takeResource) {
    std::cout << thisBuilder << " offers " << otherBuilder << " one " << giveResource << " for one " << takeResource << "." << std::endl;
    std::cout << "Does " << otherBuilder << " accept this offer?" << std::endl;
}

void printWhereBuild(const Colour thisBuilder) {
    std::cout << "Builder " << thisBuilder << ", where do you want to build a basement?" << std::endl;
}

// prints out the list of commands for begin game setting
void BoardView::beginGameHelp() {
    std::cout << "Valid Commands:" << std::endl;
    std::cout << "~ load : changes current builder's dice type to 'loaded'" << std::endl;
    std::cout << "~ fair : changes current builder's dice type to 'fair'" << std::endl;
    std::cout << "~ roll : rolls the dice and distributes resources." << std::endl;
    std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << std::endl;
    std::cout << "~ help : prints out the list of commands." << std::endl;
}

// prints out the list of commands for during game setting
void BoardView::duringGameHelp() {
    std::cout << "Valid Commands:" << std::endl;
    std::cout << "~ board : prints the current board." << std::endl;
    std::cout << "~ status : prints the current status of all builders in order from builder 0 to 3." << std::endl;
    std::cout << "~ residence : prints the residences the current builder has currently completed." << std::endl;
    std::cout << "~ build-road <edge#> : attempts to builds the road at <road#>." << std::endl;
    std::cout << "~ build-res <housing#> : attempts to builds a basement at <housing#>." << std::endl;
    std::cout << "~ improve <housing#> : attempts to improve the residence at <housing#>." << std::endl;
    std::cout << "~ trade <colour> <give> <take> : attempts to trade with builder <colour>, giving one resource of type <give> and receiving one resource of type <take>." << std::endl;
    std::cout << "~ next : passes control onto the next builder in the game." << std::endl;
    std::cout << "~ save <file> : saves the current game state to <file>." << std::endl;
    std::cout << "~ help : prints out the list of commands." << std::endl;
}
