#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

// public inhertiance of abstract class BlockFactory
class Level0Factory : public BlockFactory {
    std::vector<char> seq;
    int index;

public:
    // constructor for Level0Factory
    Level0Factory(std::string filename);
    // overriding default function to get  next Block for the specific Level0Factory
    std::unique_ptr<Block> getNext(int effects) override; 
    // overriding setSeed function
    void setSeed(int seed) override;
    // overriding setRandom function
    void setRandom(bool random, std::string file = "") override {}
    // destructor for Level0Factory
    ~Level0Factory() = default;
};

#endif // !LEVEL0_FACTORY_H
