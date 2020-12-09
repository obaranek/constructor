#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "BoardView.h"
#include "Controller.h"


const std::string eContradictingCommandLineOptions{ "ERROR: contradicting command line options: " };
const std::string eUnrecognizedCommandLineOption{ "ERROR: unrecognized command line option: " };
const std::string eInvalidSeedValue{ "ERROR: invalid seed value"};

void usage_ContradictingCommandLineOptions(std::string previousOption, std::string contradictOption) {
    std::cerr << eContradictingCommandLineOptions << previousOption << " and " << contradictOption << std::endl;
    exit(1);
}

void usage_UnrecognizedCommandLineOption(std::string option) {
    std::cerr << eUnrecognizedCommandLineOption << option << std::endl;
    exit(1);
}

void usage_invalidSeedValue() {
    std::cerr << eInvalidSeedValue << std::endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    std::unique_ptr<Controller> theController = std::make_unique<Controller>();

    // booleans to determine if other 
    bool boardPresent{ false };
    bool randomBoardPresent{ false };
    bool loadPresent{ false };

    if (argc == 1) {
        theController->initBoard();
        theController->setInitMethodCall("initBoard");

        // start the game
        theController->startGame();
    } else {
        // Loop to check for '-seed xxx'
        for (int counter = 0; counter < argc; ++counter) {
            std::string argument{ argv[counter] };
            
            if (argument == "-seed") {
                std::istringstream ss{ argv[counter + 1] };
                int seedNumber;

                if (ss >> seedNumber && seedNumber < 0) {
                    usage_invalidSeedValue();
                } else {
                    theController->setBoardSeed(seedNumber);
                    theController->setSeedValue(seedNumber);

                    ++counter;
                }
            }
        }
        
        // Loop to check for '-board xxx', '-load xxx', '-randomboard'
        for (int counter = 0; counter < argc; ++counter) {
            std::string argument{ argv[counter] };

            if (boardPresent == false && randomBoardPresent == false && loadPresent == false) {
                if (argument == "-board") {
                    std::string fileName{ argv[counter + 1] };

                    theController->initBoard(fileName);
                    theController->setInitMethodCall("-initBoard");
                    theController->setFileName(fileName);

                    boardPresent = true;
                    ++counter;

                    // start the game
                    theController->startGame();
                } else if (argument == "-load") {
                    std::string fileName{ argv[counter + 1] };

                    theController->initLoad(fileName);
                    theController->setInitMethodCall("initLoad");
                    theController->setFileName(fileName);

                    loadPresent = true;
                    ++counter;

                    // load the game
                    theController->playTurn();
                } else if (argument == "-random-board") {
                    theController->initRandomBoard();
                    theController->setInitMethodCall("initRandomBoard");

                    randomBoardPresent = true;

                    // start the game
                    theController->startGame();
                } else if (argument != "-seed") {
                    usage_UnrecognizedCommandLineOption(argument);
                }
            } else {
                if (boardPresent == true) {
                    usage_ContradictingCommandLineOptions("-board", argument);
                } else if (randomBoardPresent == true) {
                    usage_ContradictingCommandLineOptions("-random-board", argument);
                } else if (loadPresent == true) {
                    usage_ContradictingCommandLineOptions("-load", argument);
                }
            }
        }
    }
}
