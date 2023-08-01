#include "OBlock.h"

// storing rotations for OBlock as vector
const std::vector<Position> OBlock::rotation0 = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } };

OBlock::OBlock(Position p, int effects, short rotation, int startingLevel)
{
    this->effects = effects;
    this->rotation = rotation;
    start = p;
    c = 'O';
    // using switch case to set offsets for each rotation (in this case 1)
    switch (rotation) {
    case 0:
        offsets = rotation0;
        break;
    case 1:
        offsets = rotation0;
        break;
    case 2:
        offsets = rotation0;
        break;
    case 3:
        offsets = rotation0;
        break;
    }
}

void OBlock::clockwise()
{
    rotation = (rotation + 2) % 4;
    // using switch case to set offsets for each rotation (in this case 1)
    switch (rotation) {
    case 0:
        offsets = rotation0;
        break;
    case 1:
        offsets = rotation0;
        break;
    case 2:
        offsets = rotation0;
        break;
    case 3:
        offsets = rotation0;
        break;
    }
}

void OBlock::counterClockwise()
{
    rotation = (rotation + 2) % 4;
    // using switch case to set offsets for each rotation (in this case 1)
    switch (rotation) {
    case 0:
        offsets = rotation0;
        break;
    case 1:
        offsets = rotation0;
        break;
    case 2:
        offsets = rotation0;
        break;
    case 3:
        offsets = rotation0;
        break;
    }
}
