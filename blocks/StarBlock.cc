#include "StarBlock.h"

using namespace std;

const vector<Position> StarBlock::rotation0 = {{0, 0}};

StarBlock::StarBlock(int effects, int startingLevel, short rotation) {
    this->effects = effects;
    this->rotation = rotation;
    start = {5,0};
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
