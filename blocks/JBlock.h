#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"

class JBlock : public Block {
    public:
    JBlock(Position p = {0, 0}, int effects);
    void clockwise();
    void counterClockwise();
};

#endif // !JBLOCK_H