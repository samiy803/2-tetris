#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "block.h"
#include <string>

using std::string;

class Board {
    friend class Game; // Game and Player should have access to Board's privates
    friend class Player;
    vector<Block*> blocks;
    Block* currentBlock;
    Block* nextBlock;
    void drop();
    bool validBoard();
    void left();
    void right();
    void down();
    void clockwise();
    void counterClockwise();
    void gc();
    public:
    static const int COLS = 11;
    static const int ROWS = 15;
    string toString(bool includeCurrentBlock); 
};

#endif // !BOARD_H