#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"

class Level0Factory : public BlockFactory {
    public:
    Level0Factory();
    Block* getNext(int effects) override;
    ~Level0Factory() = default;
};

#endif // !LEVEL0_FACTORY_H