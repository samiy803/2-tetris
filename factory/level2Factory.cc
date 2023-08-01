#include "level2Factory.h"

std::unique_ptr<Block> Level2Factory::getNext(int effects)
{
   // equal probability for each block as desired for Level 2
    short blockType = rng() % 7;
    Block *block;
    // picking Block to construct for specific Block type
    switch (blockType) {
        case 0:
            block = new SBlock(effects, 2);
            break;
        case 1:
            block = new ZBlock(effects, 2);
            break;
        case 2:
            block = new IBlock(effects, 2);
            break;
        case 3:
            block = new JBlock(effects, 2);
            break;
        case 4:
            block = new LBlock(effects, 2);
            break;
        case 5:
            block = new OBlock(effects, 2);
            break;
        case 6:
            block = new TBlock(effects, 2);
            break;
        }
    return std::unique_ptr<Block> { block };
}

// setting seed for Level2Factory (also need to set seed for rng)
void Level2Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}
