#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include "block.h"

class BlockFactory {
    public:
    virtual Block* getNext(int effects) = 0;
};

#endif // !BLOCK_FACTORY_H