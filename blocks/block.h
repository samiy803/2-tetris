#ifndef BLOCK_H
#define BLOCK_H
#include "position.h"
#include <vector>

using std::vector;


/**
 * Block is an abstract class that represents a block in the game.
 * It has a start position, a vector of offsets, and an effects integer.
 * The start position is the position of the top left corner of the block.
 * The vector of offsets is a vector of positions that represent the offsets
 * of the other blocks in the block relative to the start position.
 * The effects integer is an integer that represents the effects using prime factorization.
*/
class Block {
    protected:
    Position start;
    vector<Position> offsets;
    int effects;
    short rotation;
    public:
    void left();
    void right();
    void down();
    void up();
    virtual void clockwise() = 0;
    vector<Position> getPositions();
    virtual void counterClockwise() = 0;
    void deleteRow(int row);
    void shiftDown(int row);
    char c;
    virtual ~Block() = default;
};
#endif // !BLOCK_H