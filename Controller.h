#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <memory>
#include "BoardModel.h"

class Controller() {
    std::unique_ptr<BoardModel> theBoardModel;
    
    Controller();

  public:
    void playTurn();
    
    void startGame();
    
    void load();
    
};

#endif