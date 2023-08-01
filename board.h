#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "block.h"
#include <string>
#include "StarBlock.h"

using std::string;

class Board {
    friend class Game; // Game and Player should have access to Board's privates
    friend class Player;
    vector<Block*> blocks;
    Block* currentBlock;
    Block* nextBlock;
    void drop();
    void dropStar();
    bool validBoard(bool includeCurrentBlock = true);
    void left(bool heavyeffect = false);
    void right(bool heavyeffect = false);
    void down(bool heavyeffect = false);
    void clockwise();
    void counterClockwise();
    int gc();
    int turn_count;
    int level = 0;
    public:
    static const int COLS = 11;
    static const int ROWS = 15;
    string toString(bool includeCurrentBlock, bool ghost = false, bool blind = false);
};

#endif // !BOARD_H