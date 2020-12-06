#include <iostream>
#include <string>
#include "Controller.h"

Controller::Controller() {}

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
                    theBoardModel->buildResidence();
                }
            } else if (userInput == "improve") { // improve <housing#>

            } else if (userInput == "trade") { // trade <colour> <give> <take>

            } else if (userInput == "save") { // save <file>

            } else if (userInput == "help") { // help
                theBoardModel->duringGameHelp();
            } else if (userInput == "next") {
                theBoardModel->next();
            } else {
                std::cout << "Invalid Command." << std::endl;
                std::cout << "Please enter 'help' for a list of valid commands." << std::endl;
            }
        }

        //
        // END PLAYER TURN
        //

        // check if won
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
                // RESTART GAME
            } else {
                isGameEnd = true;
            }
        }
    }
}

void Controller::startGame() {}

void Controller::load() {}
