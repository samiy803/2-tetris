#include "IBlock.h"

const vector<Position> IBlock::rotation0 = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
const vector<Position> IBlock::rotation1 = {{0, 3}, {1, 3}, {2, 3}, {3, 3}};

IBlock::IBlock(Position p, int effects, short rotation, int startingLevel){
    this->effects = effects;
    this->rotation = rotation;
    this->startingLevel = startingLevel;
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