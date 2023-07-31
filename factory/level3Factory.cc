#include "level3Factory.h"

Block* Level3Factory::getNext(int effects) {
    short blockType = rng() % 9;
    switch (blockType) {
        case 0:
            return new SBlock(Position{0, 0}, effects, 0);
        case 1:
            return new SBlock(Position{0, 0}, effects, 0);
        case 2:
            return new ZBlock(Position{0, 0}, effects, 0);
        case 3:
            return new ZBlock(Position{0, 0}, effects, 0);
        case 4:
            return new LBlock(Position{0, 0}, effects, 0);
        case 5:
            return new JBlock(Position{0, 0}, effects, 0);
        case 6:
            return new IBlock(Position{0, 0}, effects, 0);
        case 7:
            return new TBlock(Position{0, 0}, effects, 0);
        case 8:
            return new OBlock(Position{0, 0}, effects, 0);
    }
}

Level3Factory::~Level3Factory() {}

void Level3Factory::setSeed(int seed) {
    this->seed = seed;
    rng.seed(seed);
}