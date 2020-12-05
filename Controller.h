#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "BoardModel.h"

class Controller() {
    std::shared_ptr<BoardModel> theBoard;

  public:
    void playTurn();
    void startGame();
    void save();
    void load();
    void playAgain();
};

#endif