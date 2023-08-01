#ifndef OBlock_H
#define OBlock_H
#include "block.h"

// public inheritance of abstract Block Class
class OBlock : public Block {
    static const std::vector<Position> rotation0;

public:
    // constructor for OBlock
    OBlock(Position p = Position { 0, 0 }, int effects = 1, short rotation = 0, int startingLevel = 0);
    // specific rotations for OBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for OBlock
    ~OBlock() = default;
};

#endif // !OBLOCK_H
