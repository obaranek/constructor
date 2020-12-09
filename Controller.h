#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <memory>
#include <string>
#include "BoardModel.h"

class Controller {
    std::unique_ptr<BoardModel> theBoardModel;
    std::string initMethodCall;
    std::string fileName;
    int seedValue;
    
    Controller();

    void playTurn();
    
  public:
    void startGame();

    void initRandomBoard();

    void initBoard(std::string fileName);

    void initLoad(std::string fileName);

    void setBoardSeed(int seed);

    void setSeedValue(int seedValue);

    void setInitMethodCall(std::string initMethodCall);

    void setFileName(std::string FileName);
};

#endif
