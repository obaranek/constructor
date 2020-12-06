#include <iostream>
#include <string>
#include "Controller.h"

void Controller::playTurn() {
    // Print the board
    // Call BaordModel::printCurrTurn();
}

void Controller::startGame() {}

void Controller::save() {}

void Controller::load() {}

void Controller::playAgain() {
    std::string answerInput;
    
    std::cout << "Would you like to play again?" << std::endl;
    std::cin >> answerInput;
    
    if (answerInput != "yes" || answerInput != "no") {
        std::cout << "Would you like to play again? (yes / no)" << std::endl;
        std::cin >> answerInput;
    }

    if (answerInput == "yes") {
        // start game
    } else {
        // end game
    }
}