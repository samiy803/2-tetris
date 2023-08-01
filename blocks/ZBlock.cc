#include "ZBlock.h"

// storing rotations for ZBlock as vectors
const vector<Position> ZBlock::rotation0 = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } };
const vector<Position> ZBlock::rotation1 = { { 0, 1 }, { 0, 0 }, { 1, 0 }, { 1, -1 } };

// constructor for ZBlock
ZBlock::ZBlock(Position p, int effects, short rotation, int startingLevel)
{
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'Z';
    // using switch case to set offsets for each rotation (in this case 2)
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

void ZBlock::clockwise()
{
    rotation = (rotation + 1) % 4;
    // using switch case to set offsets for each rotation (in this case 2)
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

void ZBlock::counterClockwise()
{
    if (rotation <= 0) {
        rotation = 4 + ((rotation - 1) % 4);
    } else {
        rotation = (rotation - 1) % 4;
    }
    // using switch case to set offsets for each rotation (in this case 2)
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
