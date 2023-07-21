#ifndef SBLOCK_H
#define SBLOCK_H
#include "block.h"

class SBlock : public Block {
    public:
    SBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !SBLOCK_H