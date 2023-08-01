#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

class Level0Factory : public BlockFactory {
    vector<char> seq;
    int index;

public:
    Level0Factory(std::string filename);
    std::unique_ptr<Block> getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level0Factory() = default;
};

#endif // !LEVEL0_FACTORY_H