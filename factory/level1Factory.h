#ifndef LEVEL1_FACTORY_H
#define LEVEL1_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>
#include <memory>

class Level1Factory : public BlockFactory {
    std::mt19937 rng;

public:
    std::unique_ptr<Block> getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level1Factory() = default;
    void setRandom(bool random, std::string file = "") override {}
};

#endif // !LEVEL1_FACTORY_H