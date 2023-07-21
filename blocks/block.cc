#include "block.h"

// TODO: Handle collisions

void Block::left() {
    start.x--;
}
void Block::right() {
    start.x++;
}
void Block::down() {
    start.y++;
}