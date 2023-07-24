#include "LBlock.h"

const vector<Position> LBlock::rotation0 = {{0, 0}, {0, 1}, {0, 2}, {1, 2}};
const vector<Position> LBlock::rotation1 = {{0, 0}, {1, 0}, {2, 0}, {0, 1}};
const vector<Position> LBlock::rotation2 = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
const vector<Position> LBlock::rotation3 = {{0, 1}, {1, 1}, {2, 1}, {2, 0}};

LBlock::LBlock(Position p, int effects, short rotation) {
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'L';
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

void LBlock::clockwise() {
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

void LBlock::counterClockwise() {
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