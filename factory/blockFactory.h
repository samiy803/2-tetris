#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include "block.h"
#include "LBlock.h"

class BlockFactory {
    protected:
    int seed;
    public:
    virtual void setSeed(int seed) = 0;
    virtual Block* getNext(int effects) = 0;
    virtual ~BlockFactory(){} //hmmm
};

#endif // !BLOCK_FACTORY_H