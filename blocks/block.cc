#include "block.h"
#include "../board.h"

vector<Position> Block::getPositions() {
    vector<Position> positions;
    for (Position offset : offsets) {
        offset.x += start.x;
        offset.y += start.y;
        positions.push_back(offset);
    }
    return positions;
}

// void Block::printBlock(){
//     int maxX = 0;
//     int maxY = 0;
//     for (Position offset : offsets) {
//         if(offset.x > maxX){
//             maxX = offset.x;
//         }
//         if(offset.y > maxY){
//             maxY = offset.y;
//         }
//     }
//     char blockstr[maxX * maxY];

// }

void Block::left() {
    start.x--;
}
void Block::right() {
    start.x++;
}
void Block::down() {
    start.y++;
}

void Block::up() {
    start.y--;
}

void Block::deleteRow(int row) {
    for (auto it = offsets.begin(); it != offsets.end();) {
        if (it->y + start.y == row) {
            offsets.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Block::shiftDown(int row) {
    for (auto &offset : offsets) {
        if (offset.y + start.y < row) {
            offset.y++;
        }
    }
}

vector<Position> Block::getOffsets() {
    return offsets;
}