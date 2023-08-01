#ifndef LEVEL4_FACTORY_H
#define LEVEL4_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>
#include <memory>

class Level4Factory : public BlockFactory {
    std::mt19937 rng;

public:
    std::unique_ptr<Block> getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level4Factory() = default;
};

#endif // !LEVEL4_FACTORY_H