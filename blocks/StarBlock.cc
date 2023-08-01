#include "StarBlock.h"

using namespace std;

const vector<Position> StarBlock::rotation0 = {{0, 0}};

StarBlock::StarBlock(Position p, int effects, short rotation, int startingLevel) {
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = '*';
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
    }
}

void StarBlock::clockwise() {
    return;
}

void StarBlock::counterClockwise() {
    return;
}
