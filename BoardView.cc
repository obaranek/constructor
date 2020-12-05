#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "boardmodel.h"
#include "builder.h"



// Prints the current status of all builders in order from builder 0 to 3
void BoardView::printStatus(const std::shared_ptr<std::vector<std::shared_ptr<Builder>>> builderVectorPtr) {
    for (int counter = 0; counter < (*builderVectorPtr.size()); ++counter) {
        std::shared_ptr<Builder> currentBuilder{ *builderVectorPtr)[counter] };
        std::map<ResourceType, int> resourceMap{ builder->getResource() };

        // print the required output
        std::cout << currentBuilder->getColour() << " has ";
        std::cout << currentBuilder->getPoints() << " building points, ";
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
}

// Prints the current board
void BoardView::printBoard(const std::shared_ptr<BoardModel> board) {

}

// prints out the list of commands
void BoardView::help() {
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
