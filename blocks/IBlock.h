#ifndef IBlock_H
#define IBlock_H
#include "block.h"

class IBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;
    public:
    IBlock(Position p = Position{0, 0}, int effects = 1, short rotation = 0);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !IBLOCK_H