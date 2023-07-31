#include "level0Factory.h"

Level0Factory::Level0Factory(string filename) {
    ifstream file{filename};
    char c;
    while (file >> c) {
        if ('a' <= c && c <= 'z') {
            c += 'A' - 'a';
        }
        assert('A' <= c && c <= 'Z');
        seq.push_back(c);
    }
    index = 0;
}

Block* Level0Factory::getNext(int effects) {
    if (index >= seq.size()) {
        index = 0;
    }
    switch (seq[index++]) {
        case 'I':
            return new IBlock{Position{0, 0}, effects};
        case 'J':
            return new JBlock{Position{0, 0}, effects};
        case 'L':
            return new LBlock{Position{0, 0}, effects};
        case 'O':
            return new OBlock{Position{0, 0}, effects};
        case 'S':
            return new SBlock{Position{0, 0}, effects};
        case 'Z':
            return new ZBlock{Position{0, 0}, effects};
        case 'T':
            return new TBlock{Position{0, 0}, effects};
        default:
            throw "Invalid block type found in sequence";
    }
}

Level0Factory::~Level0Factory() {}

void Level0Factory::setSeed(int seed) {
    this->seed = seed;
}