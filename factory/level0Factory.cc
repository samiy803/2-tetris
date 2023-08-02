#include "level0Factory.h"

using namespace std;

// constructor for Level0Factory
Level0Factory::Level0Factory(string filename)
{
    // reading file appropriately to see each specific command
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
        // generating specific Block for each case of Block type
        case 'I':
            block = new IBlock(effects);
            break;
        case 'J':
            block = new JBlock(effects);
            break;
        case 'L':
            block = new LBlock(effects);
            break;
        case 'O':
            block = new OBlock(effects);
            break;
        case 'S':
            block = new SBlock(effects);
            break;
        case 'Z':
            block = new ZBlock(effects);
            break;
        case 'T':
            block = new TBlock(effects);
            break;
        default:
            throw "Invalid block type found in sequence";
    }
    return unique_ptr<Block> { block };
}
// setting seed function
void Level0Factory::setSeed(int seed)
{

    this->seed = seed;
}
