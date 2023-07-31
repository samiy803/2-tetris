#ifndef LEVEL1_FACTORY_H
#define LEVEL1_FACTORY_H

#include "blockFactory.h"
#include <vector>
#include <fstream>
#include <cassert>
#include <random>


class Level1Factory : public BlockFactory {
    std::mt19937 rng;
    public:
    Block* getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level1Factory();
};

#endif // !LEVEL1_FACTORY_H