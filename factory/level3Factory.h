#ifndef LEVEL3_FACTORY_H
#define LEVEL3_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <random>
#include <vector>
#include <memory>

class Level3Factory : public BlockFactory {
    std::mt19937 rng;
    std::vector<char> seq;
    bool random;
    int index;
public:
    std::unique_ptr<Block> getNext(int effects) override;
    void setSeed(int seed) override;
    void setRandom(bool random, std::string file = "") override;
    ~Level3Factory() = default;
    Level3Factory();
};

#endif // !LEVEL3_FACTORY_H
