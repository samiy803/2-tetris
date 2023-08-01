#include "level0Factory.h"

using namespace std;

Level0Factory::Level0Factory(string filename)
{
    ifstream file { filename };
    char c;
    while (file >> c) {
        if ('a' <= c && c <= 'z') {
            c += 'A' - 'a';
        }
        if('A' <= c && c <= 'Z')
            seq.push_back(c);
    }
    index = 0;
}

unique_ptr<Block> Level0Factory::getNext(int effects)
{
    if ((long unsigned int) index >= seq.size()) {
        index = 0;
    }

    Block* block;
    switch (seq[index++]) {
        case 'I':
            block = new IBlock { Position { 0, 0 }, effects };
            break;
        case 'J':
            block = new JBlock { Position { 0, 0 }, effects };
            break;
        case 'L':
            block = new LBlock { Position { 0, 0 }, effects };
            break;
        case 'O':
            block = new OBlock { Position { 0, 0 }, effects };
            break;
        case 'S':
            block = new SBlock { Position { 0, 0 }, effects };
            break;
        case 'Z':
            block = new ZBlock { Position { 0, 0 }, effects };
            break;
        case 'T':
            block = new TBlock { Position { 0, 0 }, effects };
            break;
        default:
            throw "Invalid block type found in sequence";
    }
    return unique_ptr<Block> { block };
}

Level0Factory::~Level0Factory() { }

void Level0Factory::setSeed(int seed)
{

    this->seed = seed;
}