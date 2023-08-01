#ifndef LEVEL2_FACTORY_H
#define LEVEL2_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>
#include <memory>

// public inhertiance of abstract class BlockFactory
class Level2Factory : public BlockFactory {
    // used to randomize blocks
    std::mt19937 rng;

public:
    // overriding default function to get next Block for the specific Level2Factory
    std::unique_ptr<Block> getNext(int effects) override;
    // overriding setSeed function for specific Level2Factory
    void setSeed(int seed) override;
    // overriding setRandom function for specific Level2Factory
    void setRandom(bool random, std::string file = "") override {}
    ~Level2Factory() = default;
    // destructor for Level2Factory
};

#endif // !LEVEL2_FACTORY_H
