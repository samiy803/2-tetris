#ifndef LEVEL1_FACTORY_H
#define LEVEL1_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>
#include <memory>

// public inhertiance of abstract class BlockFactory
class Level1Factory : public BlockFactory {
    // used to randomize blocks
    std::mt19937 rng;

public:
    // overriding default function to get next Block for the specific Level1Factory
    std::unique_ptr<Block> getNext(int effects) override;
    // overriding setSeed function for specific Level1Factory
    void setSeed(int seed) override;
    // overriding setRandom function for specific Level1Factory
    void setRandom(bool random, std::string file = "") override {}
    // destructor for Level1Factory
    ~Level1Factory() = default;
};

#endif // !LEVEL1_FACTORY_H
