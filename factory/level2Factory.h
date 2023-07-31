#ifndef LEVEL2_FACTORY_H
#define LEVEL2_FACTORY_H

#include "blockFactory.h"
#include <vector>
#include <fstream>
#include <cassert>
#include <random>


class Level2Factory : public BlockFactory {
    std::mt19937 rng;
    public:
    Block* getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level2Factory();
};

#endif // !LEVEL2_FACTORY_H