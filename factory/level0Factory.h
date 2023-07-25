#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"

class Level0Factory : public BlockFactory {
    public:
    Level0Factory();
    Block* getNext(int effects) override;
    void setSeed(int seed) override;
    ~Level0Factory();
};

#endif // !LEVEL0_FACTORY_H