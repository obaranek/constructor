#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../include/BoardView.h"
#include "../include/Controller.h"

const std::string eContradictingCommandLineOptions{
    "ERROR: contradicting command line options: "};
const std::string eUnrecognizedCommandLineOption{
    "ERROR: unrecognized command line option: "};
const std::string eInvalidSeedValue{"ERROR: invalid seed value"};

int usage_ContradictingCommandLineOptions(std::string previousOption,
                                          std::string contradictOption) {
  std::cerr << eContradictingCommandLineOptions << previousOption << " and "
            << contradictOption << std::endl;
  return 1;
}

int usage_UnrecognizedCommandLineOption(std::string option) {
  std::cerr << eUnrecognizedCommandLineOption << option << std::endl;
  return 1;
}

int usage_invalidSeedValue() {
  std::cerr << eInvalidSeedValue << std::endl;
  return 1;
}

int main(int argc, char *argv[]) {
  std::unique_ptr<Controller> theController = std::make_unique<Controller>();

  // booleans to determine if other
  bool boardPresent{false};
  bool randomBoardPresent{false};
  bool loadPresent{false};

  if (argc == 1) {
    theController->initBoard();
    theController->setInitMethodCall("initBoard");

    // start the game
    theController->startGame();
  } else {
    // Loop to check for '-seed xxx'
    for (int counter = 0; counter < argc; ++counter) {
      std::string argument{argv[counter]};

      if (argument == "-seed") {
        std::istringstream ss{argv[counter + 1]};
        int seedNumber;

        if (ss >> seedNumber && seedNumber < 0) {
          return usage_invalidSeedValue();
        } else {
          theController->setBoardSeed(seedNumber);
          theController->setSeedValue(seedNumber);

          ++counter;
        }
      }
    }

    // Loop to check for '-board xxx', '-load xxx', '-randomboard'
    for (int counter = 1; counter < argc; ++counter) {
      std::string argument{argv[counter]};

      if (boardPresent == false && randomBoardPresent == false &&
          loadPresent == false) {
        if (argument == "-board") {
          std::string fileName{argv[counter + 1]};

          try {
            theController->initBoard(fileName);
          } catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
            return 1;
          } catch (...) {
            std::cout << "Could not initialise the board" << std::endl;
            return 1;
          }
          theController->setInitMethodCall("-initBoard");
          theController->setFileName(fileName);

          boardPresent = true;
          ++counter;

          // start the game
          theController->startGame();
        } else if (argument == "-load") {
          std::string fileName{argv[counter + 1]};
          try {
            theController->initLoad(fileName);
          } catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
            return 1;
          } catch (...) {
            std::cout << "Could not initialise random board" << std::endl;
          }
          theController->setInitMethodCall("initLoad");
          theController->setFileName(fileName);

          loadPresent = true;
          ++counter;

          // load the game
          theController->playTurn();
        } else if (argument == "-random-board") {
          try {
            theController->initRandomBoard();
          } catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
            return 1;
          } catch (...) {
            std::cout << "Could not initialise random board" << std::endl;
            return 1;
          }
          theController->setInitMethodCall("initRandomBoard");

          randomBoardPresent = true;

          // start the game
          theController->startGame();
        } else if (argument != "-seed") {
          return usage_UnrecognizedCommandLineOption(argument);
        }
      } else {
        if (boardPresent == true) {
          return usage_ContradictingCommandLineOptions("-board", argument);
        } else if (randomBoardPresent == true) {
          return usage_ContradictingCommandLineOptions("-random-board",
                                                       argument);
        } else if (loadPresent == true) {
          return usage_ContradictingCommandLineOptions("-load", argument);
        }
      }
    }
  }
}
