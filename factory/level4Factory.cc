#include "level4Factory.h"

std::unique_ptr<Block> Level4Factory::getNext(int effects)
{
    Block *block;
    if (random) {
        short blockType = rng() % 9;
        switch (blockType) {
        case 0:
            block = new SBlock(effects, 3);
            break;
        case 1:
            block = new SBlock(effects, 3);
            break;
        case 2:
            block = new ZBlock(effects, 3);
            break;
        case 3:
            block = new ZBlock(effects, 3);
            break;
        case 4:
            block = new LBlock(effects, 3);
            break;
        case 5:
            block = new JBlock(effects, 3);
            break;
        case 6:
            block = new IBlock(effects, 3);
            break;
        case 7:
            block = new TBlock(effects, 3);
            break;
        case 8:
            block = new OBlock(effects, 3);
            break;
        }
    } else {
        if ((long unsigned int) index >= seq.size()) {
            index = 0;
        }
        switch (seq[index++]) {
        case 'I':
            block = new IBlock { effects, 3};
            break;
        case 'J':
            block = new JBlock { effects, 3};
            break;
        case 'L':
            block = new LBlock { effects, 3};
            break;
        case 'O':
            block = new OBlock { effects, 3};
            break;
        case 'S':
            block = new SBlock { effects, 3};
            break;
        case 'Z':
            block = new ZBlock { effects, 3};
            break;
        case 'T':
            block = new TBlock { effects, 3};
            break;
        default:
            throw "Invalid block type found in sequence";
        }
    }
    return std::unique_ptr<Block> { block };
}

void Level4Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}

void Level4Factory::setRandom(bool random, std::string file) {
    this->random = random;
    if (!random) {
        seq.clear();
        std::ifstream ifs { file };
        char c;
        while (ifs >> c) {
            if ('a' <= c && c <= 'z') {
                c += 'A' - 'a';
            }
            if ('A' <= c && c <= 'Z')
                seq.push_back(c);
        }
        index = 0;
    }
}

Level4Factory::Level4Factory() : random { true }, index { 0 } {}
