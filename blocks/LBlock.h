#ifndef LBLOCK_H
#define LBLOCK_H
#include "block.h"

// public inheritance of abstract Block Class
class LBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;
    static const std::vector<Position> rotation2;
    static const std::vector<Position> rotation3;

public:
    // constructor for LBlock
    LBlock(int effects = 1, int startingLevel = 0, short rotation = 0);
     // specific rotations for LBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for LBlock
    ~LBlock() = default;
};

#endif // !LBLOCK_H
