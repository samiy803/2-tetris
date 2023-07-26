#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"

class JBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;
    static const std::vector<Position> rotation2;
    static const std::vector<Position> rotation3;
    public:
    JBlock(Position p = Position{1, 0}, int effects = 1, short rotation = 0);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !JBLOCK_H