#include "JBlock.h"

const vector<Position> JBlock::rotation0 = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
const vector<Position> JBlock::rotation1 = {{0, 0}, {0, 1}, {1, 0}, {2, 0}};
const vector<Position> JBlock::rotation2 = {{0, 0}, {0, 1}, {0, 2}, {1, 2}};
const vector<Position> JBlock::rotation3 = {{0, 1}, {1, 1}, {2, 1}, {2, 0}};

JBlock::JBlock(Position p, int effects, short rotation) {
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'J';
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

void JBlock::clockwise() {
    rotation = (rotation - 1) % 4;
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

void JBlock::counterClockwise() {
    rotation = (rotation + 1) % 4;
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