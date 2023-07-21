#ifndef LEVEL0_FACTORY_H
#define LEVEL0_FACTORY_H

#include "blockFactory.h"

class Level0Factory : public BlockFactory {
    public:
    Block* getNext(int effects) override;
};

#endif // !LEVEL0_FACTORY_H