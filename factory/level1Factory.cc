#include "level1Factory.h"

Block* Level1Factory::getNext(int effects)
{
    short blockType = rng() % 12;
    switch (blockType) {
    case 0:
        return new SBlock(Position { 0, 0 }, effects, 0);
    case 1:
        return new ZBlock(Position { 0, 0 }, effects, 0);
    case 2:
        return new IBlock(Position { 0, 0 }, effects, 0);
    case 3:
        return new IBlock(Position { 0, 0 }, effects, 0);
    case 4:
        return new LBlock(Position { 0, 0 }, effects, 0);
    case 5:
        return new LBlock(Position { 0, 0 }, effects, 0);
    case 6:
        return new JBlock(Position { 0, 0 }, effects, 0);
    case 7:
        return new JBlock(Position { 0, 0 }, effects, 0);
    case 8:
        return new TBlock(Position { 0, 0 }, effects, 0);
    case 9:
        return new TBlock(Position { 0, 0 }, effects, 0);
    case 10:
        return new OBlock(Position { 0, 0 }, effects, 0);
    case 11:
        return new OBlock(Position { 0, 0 }, effects, 0);
    }
}

Level1Factory::~Level1Factory() { }

void Level1Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}