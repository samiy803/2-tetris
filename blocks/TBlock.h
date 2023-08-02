#ifndef TBlock_H
#define TBlock_H
#include "block.h"

// public inheritance of abstract Block Class
class TBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;
    static const std::vector<Position> rotation2;
    static const std::vector<Position> rotation3;

public:
    // constructor for TBlock
    TBlock(int effects = 1, int startingLevel = 0, short rotation = 0);
    // specific rotations for TBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for TBlock
    ~TBlock() = default;
};

#endif // !TBLOCK_H
