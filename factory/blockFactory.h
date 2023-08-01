#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "StarBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "block.h"
#include <memory>

class BlockFactory {
protected:
    int seed;

public:
    virtual void setSeed(int seed) = 0;
    virtual std::unique_ptr<Block> getNext(int effects) = 0;
    virtual ~BlockFactory() { } // hmmm
};

#endif // !BLOCK_FACTORY_H