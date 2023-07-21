#ifndef IBLOCK_H
#define IBLOCK_H
#include "block.h"

class IBlock : public Block {
    public:
    IBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !IBLOCK_H