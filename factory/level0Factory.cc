#include "level0Factory.h"

Level0Factory::Level0Factory() {}

Block* Level0Factory::getNext(int effects) {
    return new LBlock(Position{0,0}, effects, 0);
}

Level0Factory::~Level0Factory() {}

void Level0Factory::setSeed(int seed) {
    this->seed = seed;
}