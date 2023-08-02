#ifndef STARBlock_H
#define STARBlock_H
#include "block.h"

class StarBlock : public Block {
    static const std::vector<Position> rotation0;
    public:
    StarBlock(int effects = 0, int startingLevel = 4, short rotation = 0);
    void clockwise() override;
    void counterClockwise() override;
    ~StarBlock() = default;
};

#endif // !STARBLOCK_H
