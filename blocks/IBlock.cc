#include "IBlock.h"

// storing rotations for IBlock as vectors
const std::vector<Position> IBlock::rotation0 = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } };
const std::vector<Position> IBlock::rotation1 = { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } };

// constructor for IBlock
IBlock::IBlock(int effects, int startingLevel, short rotation)
{
    this->effects = effects;
    this->rotation = rotation;
    this->startingLevel = startingLevel;
    start = {0,3};
    c = 'I';
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

void IBlock::clockwise()
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

void IBlock::counterClockwise()
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
