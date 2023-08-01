#include "level2Factory.h"

Block* Level2Factory::getNext(int effects)
{
    short blockType = rng() % 7;
    switch (blockType) {
    case 0:
        return new SBlock(Position { 0, 0 }, effects, 0);
    case 1:
        return new ZBlock(Position { 0, 0 }, effects, 0);
    case 2:
        return new IBlock(Position { 0, 0 }, effects, 0);
    case 3:
        return new JBlock(Position { 0, 0 }, effects, 0);
    case 4:
        return new LBlock(Position { 0, 0 }, effects, 0);
    case 5:
        return new OBlock(Position { 0, 0 }, effects, 0);
    case 6:
        return new TBlock(Position { 0, 0 }, effects, 0);
    }
    return nullptr; // Just to make the compiler happy
}

Level2Factory::~Level2Factory() { }

void Level2Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}