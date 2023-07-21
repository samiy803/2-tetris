#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "block.h"
#include <string>

using std::string;

class Board {
    const int COLS = 11;
    const int ROWS = 15;
    vector<Block*> blocks;
    Block* currentBlock;
    string toString(); 
    void drop();
};

#endif // !BOARD_H