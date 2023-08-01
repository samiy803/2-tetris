#ifndef BOARD_H
#define BOARD_H

#include "StarBlock.h"
#include "block.h"
#include <string>
#include <vector>
#include <memory>
#include "StarBlock.h"

class Board {
    friend class Game; // Game and Player should have access to Board's privates
    friend class Player;
    std::vector<std::unique_ptr<Block>> blocks;
    std::unique_ptr<Block> currentBlock;
    std::unique_ptr<Block> nextBlock;
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
    std::string toString(bool includeCurrentBlock, bool ghost = false, bool blind = false);
    Board();
};

#endif // !BOARD_H
