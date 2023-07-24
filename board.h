#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "block.h"
#include <string>

using std::string;

class Board {
    friend class Game; // Game should have access to Board's privates
    vector<Block*> blocks;
    Block* currentBlock;
    string toString(); 
    void drop();
    public:
    static const int COLS = 11;
    static const int ROWS = 15;
};

#endif // !BOARD_H