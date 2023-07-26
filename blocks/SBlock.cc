#include "SBlock.h"

const vector<Position> SBlock::rotation0 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
const vector<Position> SBlock::rotation1 = {{0, 2}, {0, 1}, {1, 1}, {2, 0}};

SBlock::SBlock(Position p, int effects, short rotation) {
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'S';
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

void SBlock::clockwise() {
    rotation = (rotation + 2) % 4;
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

void SBlock::counterClockwise() {
    rotation = (rotation + 2) % 4;
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