#include "TBlock.h"

const vector<Position> TBlock::rotation0 = {{0, 1}, {1, 1}, {1, 0}, {2, 1}};
const vector<Position> TBlock::rotation1 = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
const vector<Position> TBlock::rotation2 = {{0, 0}, {0, 1}, {0, 2}, {1, 1}};
const vector<Position> TBlock::rotation3 = {{0, 0}, {0, 1}, {0, 2}, {1, 1}};

TBlock::TBlock(Position p, int effects, short rotation) {
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'T';
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
        case 1:
            offsets = rotation1;
            break;
        case 2:
            offsets = rotation2;
            break;
        case 3:
            offsets = rotation3;
            break;
    }
}

void TBlock::clockwise() {
    rotation = (rotation + 2) % 4;
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
        case 1:
            offsets = rotation1;
            break;
        case 2:
            offsets = rotation2;
            break;
        case 3:
            offsets = rotation3;
            break;
    }
}

void TBlock::counterClockwise() {
    rotation = (rotation + 2) % 4;
    switch (rotation) {
        case 0:
            offsets = rotation0;
            break;
        case 1:
            offsets = rotation1;
            break;
        case 2:
            offsets = rotation2;
            break;
        case 3:
            offsets = rotation3;
            break;
    }
}