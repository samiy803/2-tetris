#include "level2Factory.h"

std::unique_ptr<Block> Level2Factory::getNext(int effects)
{
    short blockType = rng() % 7;
    Block *block;
    switch (blockType) {
        case 0:
            block = new SBlock(Position { 0, 0 }, effects, 2);
        case 1:
            block = new ZBlock(Position { 0, 0 }, effects, 2);
        case 2:
            block = new IBlock(Position { 0, 0 }, effects, 2);
        case 3:
            block = new JBlock(Position { 0, 0 }, effects, 2);
        case 4:
            block = new LBlock(Position { 0, 0 }, effects, 2);
        case 5:
            block = new OBlock(Position { 0, 0 }, effects, 2);
        case 6:
            block = new TBlock(Position { 0, 0 }, effects, 2);
        }
    return std::unique_ptr<Block> { block };
}

void Level2Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}