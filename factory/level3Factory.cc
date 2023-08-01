#include "level3Factory.h"

std::unique_ptr<Block> Level3Factory::getNext(int effects)
{
    Block *block;
    if (random) {
        short blockType = rng() % 9;
        switch (blockType) {
        case 0:
            block = new SBlock(Position { 0, 0 }, effects, 0);
            break;
        case 1:
            block = new SBlock(Position { 0, 0 }, effects, 0);
            break;
        case 2:
            block = new ZBlock(Position { 0, 0 }, effects, 0);
            break;
        case 3:
            block = new ZBlock(Position { 0, 0 }, effects, 0);
            break;
        case 4:
            block = new LBlock(Position { 0, 0 }, effects, 0);
            break;
        case 5:
            block = new JBlock(Position { 0, 0 }, effects, 0);
            break;
        case 6:
            block = new IBlock(Position { 0, 0 }, effects, 0);
            break;
        case 7:
            block = new TBlock(Position { 0, 0 }, effects, 0);
            break;
        case 8:
            block = new OBlock(Position { 0, 0 }, effects, 0);
            break;
        }
    } else {
        if ((long unsigned int) index >= seq.size()) {
            index = 0;
        }
        switch (seq[index++]) {
        case 'I':
            block = new IBlock { Position { 0, 0 }, effects, 4};
            break;
        case 'J':
            block = new JBlock { Position { 0, 0 }, effects, 4};
            break;
        case 'L':
            block = new LBlock { Position { 0, 0 }, effects, 4};
            break;
        case 'O':
            block = new OBlock { Position { 0, 0 }, effects, 4};
            break;
        case 'S':
            block = new SBlock { Position { 0, 0 }, effects, 4};
            break;
        case 'Z':
            block = new ZBlock { Position { 0, 0 }, effects, 4};
            break;
        case 'T':
            block = new TBlock { Position { 0, 0 }, effects, 4};
            break;
        default:
            throw "Invalid block type found in sequence";
        }
    }
    return std::unique_ptr<Block> { block };
}

void Level3Factory::setSeed(int seed)
{
    this->seed = seed;
    rng.seed(seed);
}

void Level3Factory::setRandom(bool random, std::string file) {
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

Level3Factory::Level3Factory() : random { true }, index { 0 } {}
