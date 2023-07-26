#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"
#include <vector>
#include <fstream>
#include <cassert>

using std::string;
using std::ifstream;

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