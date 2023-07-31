#ifndef LEVEL3_FACTORY_H
#define LEVEL3_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>

class Level3Factory : public BlockFactory {
    std::mt19937 rng;

public:
    Block* getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level3Factory();
};

#endif // !LEVEL3_FACTORY_H