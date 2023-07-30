#ifndef LEVEL4_FACTORY_H
#define LEVEL4_FACTORY_H

#include "blockFactory.h"
#include <vector>
#include <fstream>
#include <cassert>
#include <random>


class Level4Factory : public BlockFactory {
    std::mt19937 rng;
    public:
    Block* getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level4Factory();
};

#endif // !LEVEL4_FACTORY_H