#ifndef SBlock_H
#define SBlock_H
#include "block.h"

// public inheritance of abstract Block Class
class SBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;

public:
    // constructor for SBlock
    SBlock(int effects = 1, int startingLevel = 0, short rotation = 0);
    // specific rotations for SBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for SBlock
    ~SBlock() = default;
};

#endif // !SBLOCK_H
