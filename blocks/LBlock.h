#ifndef LBLOCK_H
#define LBLOCK_H
#include "block.h"

class LBlock : public Block {
    public:
    LBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !LBLOCK_H