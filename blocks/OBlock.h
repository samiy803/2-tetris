#ifndef OBLOCK_H
#define OBLOCK_H
#include "block.h"

class OBlock : public Block {
    public:
    OBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !OBLOCK_H