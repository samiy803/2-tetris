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

void Block::notify(int row) {
    for (Position &pos : offsets) {
        if (pos.y + start.y < row) {
            pos.y++;
        }
        else if (pos.y + start.y == row) {
            // Erase this offset
            
        }

    }
}