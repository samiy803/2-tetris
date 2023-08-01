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

/* Abstract block factory (for factory pattern) 
where specific factories are used for each level (inherit this class)
*/
class BlockFactory {
protected:
    int seed;

public:
    // function to setsSeed 
    virtual void setSeed(int seed) = 0;
    // get Next Block function for BlockFactory
    virtual std::unique_ptr<Block> getNext(int effects) = 0;
    // virtual destructor for BlockFactory
    virtual ~BlockFactory() {}; 
    // set Random function 
    virtual void setRandom(bool random, std::string file = "") = 0;
};

#endif // !BLOCK_FACTORY_H
