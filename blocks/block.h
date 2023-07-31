#ifndef BLOCK_H
#define BLOCK_H
#include "position.h"
#include <vector>
#include <iostream>
#include <memory>


using std::vector;
using std::iostream;


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
    // heavy is 2
    // very heavy is 3
    // blind is 5
    // force is 7
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
    void printBlock(bool player1);
    int startingLevel;
    char c;
    vector<Position> getOffsets();
    virtual ~Block() = default;
    Block *clone();
};
#endif // !BLOCK_H