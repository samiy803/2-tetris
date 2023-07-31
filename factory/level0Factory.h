#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"
#include <cassert>
#include <fstream>
#include <vector>

using std::ifstream;
using std::string;

class Level0Factory : public BlockFactory {
    vector<char> seq;
    int index;

public:
    Level0Factory(string filename);
    Block* getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level0Factory();
};

#endif // !LEVEL0_FACTORY_H