#ifndef STARBlock_H
#define STARBlock_H
#include "block.h"

class StarBlock : public Block {
    static const std::vector<Position> rotation0;

public:
    StarBlock(Position p = Position { 5, 0 }, int effects = 0, short rotation = 0, int startingLevel = 4);
    void clockwise() override;
    void counterClockwise() override;
};

#endif // !STARBLOCK_H