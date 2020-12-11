#include "Controller.h"
#include "Colour.h"
#include "ResourceType.h"
#include <fstream>
#include <iostream>
#include <string>

Controller::Controller()
    : theBoardModel{std::make_unique<BoardModel>()},
      initMethodCall{""}, fileName{""}, seedValue{-1} {}

void Controller::playTurn() {
  bool IsGameEnd{false};

  //
  // BEGIN PLAYER TURN
  //
  while (IsGameEnd == false) {
    theBoardModel->printBoard();
    theBoardModel->printCurrBuilderTurn();

    std::string userInput;
    std::cin >> userInput;

    // continue to set the dice type until user types 'roll'
    while (userInput != "roll") {
      if (userInput == "loaded") {
        theBoardModel->setDice('L');
      } else if (userInput == "fair") {
        theBoardModel->setDice('F');
      } else if (userInput == "status") {
        theBoardModel->printStatus();
      } else if (userInput == "help") {
        theBoardModel->beginGameHelp();
      } else {
        std::cout << "Invalid Input." << std::endl;
        std::cout << "Please enter 'help' for a list of valid commands."
                  << std::endl;
      }

      std::cin >> userInput;
    }

    // final dice type or dice type used last round
    char diceType{theBoardModel->getDiceType()};

    // variable to store dice number
    int diceValue;

    // if diceType == 'L' ask for user input and validate user input
    if (diceType == 'L') {
      std::cout << "Input a roll between 2 and 12:" << std::endl;
      std::cin >> diceValue;

      while (!(2 <= diceValue && diceValue <= 12)) {
        std::cout << "Invalid roll." << std::endl;
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
      std::cout << "¿" << std::endl;
      std::cin >> userInput;

      // READS EOF, SAVE AND EXIT.
      if (std::cin.eof()) {
        std::string eofSaveFile{"backup.sv"};
        // TODO: uncomment save
        // theBoardModel->save(eofSaveFile);

        std::cout << "Saving to " << eofSaveFile << "..." << std::endl;
        exit(0);
      }

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

        if (!(1 <= edgeValue && edgeValue <= 70)) {
          std::cout << "Invalid <road#>" << std::endl;
        } else {
          theBoardModel->BuildRoad(edgeValue);
        }
      } else if (userInput == "build-res") { // build-res <housing#>
        int vertexValue;
        std::cin >> vertexValue;

        if (!(0 <= vertexValue && vertexValue <= 53)) {
          std::cout << "Invalid <housing#>" << std::endl;
        } else {
          theBoardModel->buildResidence(vertexValue, false);
        }
      } else if (userInput == "improve") { // improve <housing#>
        int vertexValue;
        std::cin >> vertexValue;

        if (!(0 <= vertexValue && vertexValue <= 53)) {
          std::cout << "Invalid <housing#>" << std::endl;
        } else {
          theBoardModel->improveResidence(vertexValue);
        }
      } else if (userInput == "trade") { // trade <colour> <give> <take>
        // Reads in the other player's color
        std::string otherPlayerColour;
        std::cin >> otherPlayerColour;

        Colour otherBuilderColour;

        if (otherPlayerColour[0] == 'B' ||
            otherPlayerColour[0] == 'b') { // blue
          otherBuilderColour = BLUE;
        } else if (otherPlayerColour[0] == 'R' ||
                   otherPlayerColour[0] == 'r') { // red
          otherBuilderColour = RED;
        } else if (otherPlayerColour[0] == 'O' ||
                   otherPlayerColour[0] == 'o') { // orange
          otherBuilderColour = ORANGE;
        } else if (otherPlayerColour[0] == 'Y' ||
                   otherPlayerColour[0] == 'y') { // yellow
          otherBuilderColour = YELLOW;
        } else {
          std::cout << "Invalid <colour>" << std::endl;
          continue;
        }

        // Reads in the offered resource
        std::string giveResource;
        std::cin >> giveResource;

        ResourceType giveResourceType;

        if (giveResource[0] == 'B' || giveResource[0] == 'b') { // brick
          giveResourceType = ResourceType::BRICK;
        } else if (giveResource[0] == 'E' || giveResource[0] == 'e') { // energy
          giveResourceType = ResourceType::ENERGY;
        } else if (giveResource[0] == 'G' || giveResource[0] == 'g') { // glass
          giveResourceType = ResourceType::GLASS;
        } else if (giveResource[0] == 'H' || giveResource[0] == 'h') { // heat
          giveResourceType = ResourceType::HEAT;
        } else if (giveResource[0] == 'W' || giveResource[0] == 'w') { // wifi
          giveResourceType = ResourceType::WIFI;
        } else if (giveResource[0] == 'P' || giveResource[0] == 'p') { // park
          giveResourceType = ResourceType::PARK;
        } else {
          std::cout << "Invalid <give>" << std::endl;
          continue;
        }

        // Reads in the requested resource
        std::string takeResource;
        std::cin >> takeResource;

        ResourceType takeResourceType;

        if (giveResource[0] == 'B' || giveResource[0] == 'b') { // brick
          giveResourceType = ResourceType::BRICK;
        } else if (giveResource[0] == 'E' || giveResource[0] == 'e') { // energy
          giveResourceType = ResourceType::ENERGY;
        } else if (giveResource[0] == 'G' || giveResource[0] == 'g') { // glass
          giveResourceType = ResourceType::GLASS;
        } else if (giveResource[0] == 'H' || giveResource[0] == 'h') { // heat
          giveResourceType = ResourceType::HEAT;
        } else if (giveResource[0] == 'W' || giveResource[0] == 'w') { // wifi
          giveResourceType = ResourceType::WIFI;
        } else if (giveResource[0] == 'P' || giveResource[0] == 'p') { // park
          giveResourceType = ResourceType::PARK;
        } else {
          std::cout << "Invalid <take>" << std::endl;
          continue;
        }

        std::shared_ptr<Builder> currBuilder{theBoardModel->getCurrBuilder()};

        // print required output to display
        theBoardModel->printTradeResources(otherBuilderColour, giveResourceType,
                                           takeResourceType);

        // wait for reply (yes / no)
        std::string acceptTrade;
        std::cin >> acceptTrade;

        while (acceptTrade != "yes" || acceptTrade != "no") {
          std::cout << "Invalid input." << std::endl;
          theBoardModel->printTradeResources(
              otherBuilderColour, giveResourceType, takeResourceType);
          std::cin >> acceptTrade;
        }

        if (acceptTrade == "yes") {

          //@TODO: uncomment when done
          // theBoardModel->tradeResource(otherBuilderColour, giveResourceType,
          // takeResourceType);
        }

      } else if (userInput == "save") { // save <file>
        std::string fileName;
        std::cin >> fileName;

        // TODO: uncomment when done
        // theBoardModel->save(fileName);
      } else if (userInput == "help") { // help
        theBoardModel->duringGameHelp();
      } else if (userInput == "next") {
        theBoardModel->next();
      } else {
        std::cout << "Invalid command." << std::endl;
        std::cout << "Please enter 'help' for a list of valid commands."
                  << std::endl;
      }
    }

    //
    // END PLAYER TURN
    //
    bool isPlayerWon{theBoardModel->checkWinner()};

    if (isPlayerWon == true) {
      std::cout << "Congratulations! "
                << (theBoardModel->getCurrBuilder())->getColour() << " has won!"
                << std::endl;
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
        IsGameEnd = true;
      }
    }
  }
}

void Controller::startGame() {
  // creates a new board for a new game

  if (initMethodCall.empty()) {
    initBoard();
  } else if (initMethodCall == "initLoad") {
    initLoad(fileName);
  } else if (initMethodCall == "initBoard") {
    if (fileName == "") {
      initBoard();
    } else {
    initBoard(fileName);

  }} else {
    initRandomBoard();
  }

  // if user gives a seed value
  if (seedValue >= 0) {
    setSeedValue(seedValue);
  }

  theBoardModel->printBoard();

  // Building initial houses
  for (int counter = 0; counter < 8; ++counter) {
    int userVertexInput;
    bool acceptHouse = false;

    do {
      // outputs the start-of-game where-to-build message
      theBoardModel->printWhereBuild();

      // get user input
      std::cin >> userVertexInput;
      
      if(0 <= userVertexInput && userVertexInput <= 53){
        try{ // Try building the residence
          theBoardModel->buildResidence(userVertexInput, true);
          acceptHouse = true;
        } catch(std::logic_error e){
          std::cout << e.what() << std::endl; 
        }
      }
    } while (!acceptHouse);

    // built house, change builder
    if (0 <= counter && counter <= 2) {
      theBoardModel->next();
    } else if (4 <= counter && counter <= 7) {
      theBoardModel->prevBuilder();
    }
  }

  // begin play turn after start game procedure (loop)
  playTurn();
}

// TODO: uncomment when implemented
void Controller::initRandomBoard() { /**theBoardModel->initRandomBoard(); **/
}

void Controller::initBoard(std::string fileName) {
  theBoardModel->initBoard(fileName);
}

void Controller::initBoard() { theBoardModel->initBoard(); }

void Controller::initLoad(std::string fileName) {
  theBoardModel->initLoad(fileName);
}

void Controller::setBoardSeed(int seed) { theBoardModel->setSeed(seed); }

void Controller::setSeedValue(int seed) { seedValue = seed; }

void Controller::setInitMethodCall(std::string initMethod) {
  initMethodCall = initMethod;
}

void Controller::setFileName(std::string inputFileName) {
  fileName = inputFileName;
}
