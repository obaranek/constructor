#ifndef _BOARDVIEW_H_
#define _BOARDVIEW_H_
#include <vector>
#include <memory>



class BoardView() {
    // Prints the current status of all builders in order from builder 0 to 3
    void printStatus(const std::shared_ptr<std::vector<std::shared_ptr<Builder>>> builderVectorPtr);

    // Prints the residence owned by the builder
    void printResidence(const std::shared_ptr<Builder> builder);

    // Prints the current board
    void printBoard(const std::shared_ptr<BoardModel> board);

    // prints out the list of commands
    void help();
};

#endif