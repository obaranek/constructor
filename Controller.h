#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "BoardModel.h"

class Controller() {
    std::unique_ptr<BoardModel> theBoardModel;
    
    Controller();

  public:
    void playTurn();
    
    void startGame();
    
    void save();
    
    void load();
    
    void playAgain();
};

#endif