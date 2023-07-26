#include "IBlock.h"

const vector<Position> IBlock::rotation0 = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
const vector<Position> IBlock::rotation1 = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};

IBlock::IBlock(Position p, int effects, short rotation) {
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'I';
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
        case 1:
            offsets = rotation1;
            break;
        case 2:
            offsets = rotation0;
            break;
        case 3:
            offsets = rotation1;
            break;
    }
}

void IBlock::clockwise() {
    rotation = (rotation + 1) % 4;
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
        case 1:
            offsets = rotation1;
            break;
        case 2:
            offsets = rotation0;
            break;
        case 3:
            offsets = rotation1;
            break;
    }
}

void IBlock::counterClockwise() {
    rotation = (rotation - 1) % 4;
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
        case 1:
            offsets = rotation1;
            break;
        case 2:
            offsets = rotation0;
            break;
        case 3:
            offsets = rotation1;
            break;
    }
}