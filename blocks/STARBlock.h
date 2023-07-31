#ifndef STARBlock_H
#define STARBlock_H
#include "block.h"

class STARBlock : public Block {
    static const std::vector<Position> rotation0;
    public:
    STARBlock(Position p = Position{0, 5}, int effects = 1, short rotation = 0, int startingLevel = 0);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !SBLOCK_H