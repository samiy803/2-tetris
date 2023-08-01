#include "TBlock.h"

// storing rotations for TBlock as vectors
const vector<Position> TBlock::rotation0 = { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 1, 1 } };
const vector<Position> TBlock::rotation1 = { { 0, 0 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };
const vector<Position> TBlock::rotation2 = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 1, 0 } };
const vector<Position> TBlock::rotation3 = { { 0, -1 }, { 0, 0 }, { 0, 1 }, { 1, 0 } };

// constructor for TBlock
TBlock::TBlock(Position p, int effects, short rotation, int startingLevel)
{
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'T';
    // using switch case to set offsets for each rotation (in this case 4)
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

void TBlock::clockwise()
{
    rotation = (rotation + 1) % 4;
    // using switch case to set offsets for each rotation (in this case 4)
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

void TBlock::counterClockwise()
{
    if (rotation <= 0) {
        rotation = 4 + ((rotation - 1) % 4);
    } else {
        rotation = (rotation - 1) % 4;
    }
    // using switch case to set offsets for each rotation (in this case 4)
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
