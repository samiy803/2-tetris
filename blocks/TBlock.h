#ifndef TBLOCK_H
#define TBLOCK_H
#include "block.h"

class TBlock : public Block {
    public:
    TBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !TBLOCK_H