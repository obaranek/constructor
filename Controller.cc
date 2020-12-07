#include <iostream>
#include <fstream>
#include <string>
#include "Controller.h"
#include "Colour.h"
#include "ResourceType.h"

Controller::Controller() {
    theBoardModel{ std::make_unique<BoardModel>() }
}

void Controller::playTurn() {
    bool IsGameEnd{ false };

    //
    // BEGIN PLAYER TURN
    //
    while (IsGameEnd == false) {
        theBoardModel->printBoard();
        theBoardModel->printCurrBuilderTurn();

        std::string userInput;
        std::cin >> userInput;

        // continue to set the dice type until user types 'roll'
        while(userInput != "roll") {
            if (userInput == "loaded") {
                theBoardModel->setDice('L');
            } else if (userInput == "fair") {
                theBoardModel->setDice('F');
            } else if (userInput == 'status') {
                theBoardModel->printStatus();
            } else if (userInput == "help") {
                theBoardModel->beginGameHelp();
            } else {
                std::cout << "Invalid Input." << std::endl;
                std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
            }

            std::cin >> userInput;
        }
        
        // final dice type or dice type used last round
        char diceType{ theBoardModel->getDiceType() };
        
        // variable to store dice number
        int diceValue;
        
        // if diceType == 'L' ask for user input and validate user input
        if (diceType == 'L') {
            std::cout << "Input a roll between 2 and 12:" << std::endl;
            std::cin >> diceValue;

            while(! (2 <= diceValue && diceValue <= 12)) {
                std::cout << "Invalid roll." <<  std::endl;
                std::cout << "Input a roll between 2 and 12:" << std::endl;
                std::cin >> diceValue;
            }   
        } else { // diceType == 'F'
            diceValue = theBoardModel->rollDice();
        }

        // play the roll by calling playRoll and pass in the dice value
        theBoardModel->playRoll(diceValue);

        //
        // DURING PLAYER TURN
        //
        while (userInput != "next") {
            std::cin >> userInput;

            // board
            if (userInput == "board") {
                theBoardModel->printBoard();
            } else if (userInput == "status") { // status
                theBoardModel->printStatus();
            } else if (userInput == "residence") { // residence
                theBoardModel->printResidences();
            } else if (userInput == "build-road") { // build-road <road#>
                int edgeValue;
                std::cin >> edgeValue;

                if (! (1 <= edgeValue && edgeValue <= 70)) {
                    std::cout << "Invalid <road#>" << std::endl;
                } else {
                    theBoardModel->buildRoad(edgeValue);
                }
            } else if (userInput == "build-res") { // build-res <housing#>
                int vertexValue;
                std::cin >> vertexValue;

                if (! (0 <= vertexValue && vertexValue <= 53)) {
                    std::cout << "Invalid <housing#>" << std::endl;
                } else {
                    theBoardModel->buildResidence(vertexValue, false);
                }
            } else if (userInput == "improve") { // improve <housing#>
                int vertexValue;
                std::cin >> vertexValue;

                if (! (0 <= vertexValue && vertexValue <= 53)) {
                    std::cout << "Invalid <housing#>" << std::endl;
                } else {
                    theBoardModel->improveResidence(vertexValue);
                }
            } else if (userInput == "trade") { // trade <colour> <give> <take>
                    // Reads in the other player's color
                    Colour otherPlayerColour;
                    std::cin >> otherPlayerColour;

                    // Reads in the offered resource
                    ResourceType giveResource;
                    std::cin >> giveResource;

                    // Reads in the requested resource
                    ResourceType takeResource;
                    std::cin >> takeResource;
                    
                    std::shared_ptr<Builder> currBuilder{ theBoardModel->getCurrBuilder() };

                    // print required output to display
                    theBoardModel->printTradeResource(currBuilder->getColour(), otherPlayerColour, giveResource, takeResource);

                    // wait for reply (yes / no)
                    std::string acceptTrade;
                    std::cin >> acceptTrade;

                    while (acceptTrade != "yes" || acceptTrade != "no") {
                        std::cout << "Invalid input." << std::endl;
                        theBoardModel->printTradeResource(currBuilder->getColour(), otherPlayerColour, giveResource, takeResource);
                        std::cin >> acceptTrade;
                    }

                    if (acceptTrade == "yes") {
                        theBoardModel->tradeResources(otherPlayer, giveResource, takeResource);
                    }

            } else if (userInput == "save") { // save <file>
                    std::string fileName;
                    std::cin >> fileName;

                    theBoardModel->save(fileName);
            } else if (userInput == "help") { // help
                theBoardModel->duringGameHelp();
            } else if (userInput == "next") {
                theBoardModel->next();
            } else {
                std::cout << "Invalid command." << std::endl;
                std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
            }
        }

        //
        // END PLAYER TURN
        //
        bool isPlayerWon{ theBoardModel->checkWinner() };

        if (isPlayerWon == true) {
            std::cout << "Would you like to play again?" << std::endl;

            std::string userReplayInput;
            std::cin >> userReplayInput;

            while (userReplayInput != "yes" || userReplayInput != "no") {
                std::cout << "Invalid input." << std::endl;
                std::cout << "Would you like to play again? (yes / no)" << std::endl;
                std::cin >> userReplayInput;
            }

            if (userReplayInput == "yes") {
                startGame();
            } else {
                isGameEnd = true;
            }
        }
    }
}

void Controller::startGame() {
    // creates a new board for a new game
    theBoardModel->init(); // OMAR, HOW DO YOU RESTART GAME WITH INIT()?

    for(int counter = 0; counter < 8; ++counter) {
        int userVertexInput;

        do {
            // outputs the start-of-game where-to-build message
            theBoardModel->printWhereBuild();

            // get user input
            std::cin >> userVertexInput;
        } while (! (0 <= userVertexInput && userVertexInput <= 53))

        // Build the residence
        theBoardModel->buildResidence(userVertexInput, true);

        if (0 <= counter && counter <= 2) {
            theBoardModel->next();
        } else if (4 <= counter && counter <= 7) {
            theBoardModel->previous();
        }
    }
    
    // begin play turn after start game procedure (loop)
    playTurn();
}

void Controller::load() {
    std::ifstream loadFile;
    theBoardModel->load(loadFile);
}
