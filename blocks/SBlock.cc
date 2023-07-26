#include "SBlock.h"

const vector<Position> SBlock::rotation0 = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
const vector<Position> SBlock::rotation1 = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};

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

void SBlock::counterClockwise() {
    if(rotation <= 0){
        rotation = 4 + ((rotation - 1) % 4);
    }else{
        rotation = (rotation - 1) % 4;
    }
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