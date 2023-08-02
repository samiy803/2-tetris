#include "level1Factory.h"

std::unique_ptr<Block> Level1Factory::getNext(int effects)
{
    /* equal probabilities for each block (1/6)
       except 1/12 probablity for SBlock and ZBlock
       as desired for this level
    */
    short blockType = rng() % 12;
    Block *block;
    // picking Block to construct for specific Block type
    std::cout << blockType << std::endl;
    switch (blockType) {
        case 0:
            block = new SBlock(effects, 1);
            break;
        case 1:
            block = new ZBlock(effects, 1);
            break;
        case 2:
            block = new IBlock(effects, 1);
            break;
        case 3:
            block = new IBlock(effects, 1);
            break;
        case 4:
            block = new LBlock(effects, 1);
            break;
        case 5:
            block = new LBlock(effects, 1);
            break;
        case 6:
            block = new JBlock(effects, 1);
            break;
        case 7:
            block = new JBlock(effects, 1);
            break;
        case 8:
            block = new TBlock(effects, 1);
            break;
        case 9:
            block = new TBlock(effects, 1);
            break;
        case 10:
            block = new OBlock(effects, 1);
            break;
        case 11:
            block = new OBlock(effects, 1);
            break;
    }
    return std::unique_ptr<Block> { block };
}


// setting seed for Level1Factory (also need to set seed for rng)
void Level1Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}
