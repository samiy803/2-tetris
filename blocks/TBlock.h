#ifndef TBlock_H
#define TBlock_H
#include "block.h"

class TBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;
    static const std::vector<Position> rotation2;
    static const std::vector<Position> rotation3;
    public:
    TBlock(Position p = Position{0, 0}, int effects = 1, short rotation = 0, int startingLevel = 0);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !TBLOCK_H