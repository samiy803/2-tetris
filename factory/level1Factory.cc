#include "level1Factory.h"

std::unique_ptr<Block> Level1Factory::getNext(int effects)
{
    short blockType = rng() % 12;
    Block *block;
    switch (blockType) {
        case 0:
            block = new SBlock(Position { 0, 0 }, effects, 1);
        case 1:
            block = new ZBlock(Position { 0, 0 }, effects, 1);
        case 2:
            block = new IBlock(Position { 0, 0 }, effects, 1);
        case 3:
            block = new IBlock(Position { 0, 0 }, effects, 1);
        case 4:
            block = new LBlock(Position { 0, 0 }, effects, 1);
        case 5:
            block = new LBlock(Position { 0, 0 }, effects, 1);
        case 6:
            block = new JBlock(Position { 0, 0 }, effects, 1);
        case 7:
            block = new JBlock(Position { 0, 0 }, effects, 1);
        case 8:
            block = new TBlock(Position { 0, 0 }, effects, 1);
        case 9:
            block = new TBlock(Position { 0, 0 }, effects, 1);
        case 10:
            block = new OBlock(Position { 0, 0 }, effects, 1);
        case 11:
            block = new OBlock(Position { 0, 0 }, effects, 1);
    }
    return std::unique_ptr<Block> { block };
}


void Level1Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}