#ifndef LEVEL2_FACTORY_H
#define LEVEL2_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>
#include <memory>

class Level2Factory : public BlockFactory {
    std::mt19937 rng;

public:
    std::unique_ptr<Block> getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level2Factory() = default;
};

#endif // !LEVEL2_FACTORY_H