#include "STARBlock.h"

const vector<Position> STARBlock::rotation0 = {{0, 0}};

STARBlock::STARBlock(Position p, int effects, short rotation, int startingLevel) {
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

void STARBlock::clockwise() {
    return;
}

void STARBlock::counterClockwise() {
    return;
}





