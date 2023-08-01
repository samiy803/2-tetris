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
    std::vector<char> seq;
    bool random;
    int index;
public:
    std::unique_ptr<Block> getNext(int effects) override;
    void setSeed(int seed) override;
    void setRandom(bool random, std::string file = "") override;
    ~Level4Factory() = default;
    Level4Factory();
};

#endif // !LEVEL4_FACTORY_H