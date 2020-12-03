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
        std::cout << residenceMap[Brick] << " brick, ";
        std::cout << residenceMap[Energy] << " energy, ";
        std::cout << residenceMap[Glass] << " glass, ";
        std::cout << residenceMap[Heat] << " heat, and ";
        std::cout << residenceMap[Brick] << " WiFi." << std::endl;   
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
std::cout << "Valid commands:" << std::endl;
std::cout << "board" << std::endl;
std::cout << "status" << std::endl;
std::cout << "residence" << std::endl;
std::cout << "build-road <edge#>" << std::endl;
std::cout << "build-res <housing#>" << std::endl;
std::cout << "improve <housing#>" << std::endl;
std::cout << "trade <colour> <give> <take>" << std::endl;
std::cout << "next" << std::endl;
std::cout << "save <file>" << std::endl;
std::cout << "help" << std::endl;
}
