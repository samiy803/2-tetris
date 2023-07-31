#ifndef ZBlock_H
#define ZBlock_H
#include "block.h"

class ZBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;

public:
    ZBlock(Position p = Position { 0, 0 }, int effects = 1, short rotation = 0, int startingLevel = 0);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !ZBLOCK_H