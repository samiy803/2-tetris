#ifndef STARBlock_H
#define STARBlock_H
#include "block.h"

// this block is specifically used to create a divider when player is in level 4
// public inheritance of abstract Block Class
class StarBlock : public Block {
    static const std::vector<Position> rotation0;

public:
    // constructor for StarBlock
    StarBlock(Position p = Position { 5, 0 }, int effects = 0, short rotation = 0, int startingLevel = 4);
    // specific rotations for StarBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for StarBlock
    ~StarBlock() = default;
};

#endif // !STARBLOCK_H
