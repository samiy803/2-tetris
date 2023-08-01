#ifndef SBlock_H
#define SBlock_H
#include "block.h"

class SBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;

public:
    SBlock(Position p = Position { 0, 0 }, int effects = 1, short rotation = 0, int startingLevel = 0);
    void clockwise() override;
    void counterClockwise() override;
    ~SBlock() = default;
};

#endif // !SBLOCK_H