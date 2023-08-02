#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"

// public inheritance of abstract Block Class
class JBlock : public Block {
    static const std::vector<Position> rotation0;
    static const std::vector<Position> rotation1;
    static const std::vector<Position> rotation2;
    static const std::vector<Position> rotation3;

public:
// constructor for JBlock
    JBlock(int effects = 1, int startingLevel = 0, short rotation = 0);
    // specific rotations for JBlock (override the default)
    void clockwise() override;
    void counterClockwise() override;
    // destructor for JBlock
    ~JBlock() = default;
};

#endif // !JBLOCK_H
