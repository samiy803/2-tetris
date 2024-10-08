#include "JBlock.h"

// storing rotations for JBlock as vectors
const std::vector<Position> JBlock::rotation0 = { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 0, 2 } };
const std::vector<Position> JBlock::rotation1 = { { 0, 1 }, { 0, 2 }, { 1, 2 }, { 2, 2 } };
const std::vector<Position> JBlock::rotation2 = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 } };
const std::vector<Position> JBlock::rotation3 = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 2 } };

JBlock::JBlock(int effects, int startingLevel, short rotation)
{
    this->effects = effects;
    this->rotation = rotation;
    this->startingLevel = startingLevel;
    start = {0,3};
    c = 'J';
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

void JBlock::clockwise()
{
    rotation = (rotation + 1) % 4;
    // using switch case to set offsts for each rotation (in this case 4)
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

void JBlock::counterClockwise()
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
