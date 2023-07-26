#ifndef OBlock_H
#define OBlock_H
#include "block.h"

class OBlock : public Block {
    static const std::vector<Position> rotation0;
    public:
    OBlock(Position p = Position{0, 0}, int effects = 1, short rotation = 0);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !OBLOCK_H