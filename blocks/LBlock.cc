#include "LBlock.h"

// storing rotations for LBlock as vectors
const std::vector<Position> LBlock::rotation0 = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 } };
const std::vector<Position> LBlock::rotation1 = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 0, 2 } };
const std::vector<Position> LBlock::rotation2 = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } };
const std::vector<Position> LBlock::rotation3 = { { 0, 2 }, { 1, 2 }, { 2, 2 }, { 2, 1 } };

LBlock::LBlock(Position p, int effects, short rotation, int startingLevel)
{
    this->effects = effects;
    this->rotation = rotation;
    this->startingLevel = startingLevel;
    start = p;
    c = 'L';
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

void LBlock::clockwise()
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

void LBlock::counterClockwise()
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
