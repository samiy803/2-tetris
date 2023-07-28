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
    for (auto it = offsets.begin(); it != offsets.end();) {
        if (it->y + start.y < row) {
            it->y++;
        }
        else if (it->y + start.y == row) {
            offsets.erase(it);
        }
        else {
            ++it;
        }
    }
}