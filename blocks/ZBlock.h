#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "block.h"

class ZBlock : public Block {
    public:
    ZBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !ZBLOCK_H