#ifndef ZBlock_H
#define ZBlock_H
#include "block.h"

// public inheritance of abstract Block Class
class ZBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;

public:
     // constructor for ZBlock
    ZBlock(int effects = 1, int startingLevel = 0, short rotation = 0);
    // specific rotations for ZBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for ZBlock
    ~ZBlock() = default;
};

#endif // !ZBLOCK_H
