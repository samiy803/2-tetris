#include "level3Factory.h"

std::unique_ptr<Block> Level3Factory::getNext(int effects)
{
    short blockType = rng() % 9;
    Block *block;
    switch (blockType) {
    case 0:
        block = new SBlock(Position { 0, 0 }, effects, 0);
    case 1:
        block = new SBlock(Position { 0, 0 }, effects, 0);
    case 2:
        block = new ZBlock(Position { 0, 0 }, effects, 0);
    case 3:
        block = new ZBlock(Position { 0, 0 }, effects, 0);
    case 4:
        block = new LBlock(Position { 0, 0 }, effects, 0);
    case 5:
        block = new JBlock(Position { 0, 0 }, effects, 0);
    case 6:
        block = new IBlock(Position { 0, 0 }, effects, 0);
    case 7:
        block = new TBlock(Position { 0, 0 }, effects, 0);
    case 8:
        block = new OBlock(Position { 0, 0 }, effects, 0);
    }
    return std::unique_ptr<Block> { block };
}

Level3Factory::~Level3Factory() { }

void Level3Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}