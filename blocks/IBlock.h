#ifndef IBlock_H
#define IBlock_H
#include "block.h"

// public inheritance of abstract Block Class
class IBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;

public:
    // constructor for IBlock
    IBlock(Position p = Position { 0, 0 }, int effects = 1, short rotation = 0, int startingLevel = 0);
    // specific rotations for IBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for IBlock
    ~IBlock() = default;
};

#endif // !IBLOCK_H
