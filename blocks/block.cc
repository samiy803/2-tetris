#include "block.h"
#include "../board.h"
#include "level0Factory.h"

vector<Position> Block::getPositions()
{
    //vector of Positions (coordinates) for that specific block
    vector<Position> positions;
    for (Position offset : offsets) {
        // adding start Position (x and y coordinate to offsets)
        offset.x += start.x;
        offset.y += start.y;
        // add offset to positions array
        positions.push_back(offset);
    }
    return positions;
}

//functions to move block
void Block::left()
{
    start.x--;
}
void Block::right()
{
    start.x++;
}
void Block::down()
{
    start.y++;
}

void Block::up()
{
    start.y--;
}

//functions to delete the rows when the row is full
void Block::deleteRow(int row)
{
    for (auto it = offsets.begin(); it != offsets.end();) {
        if (it->y + start.y == row) {
            // erasing offset from out vector
            offsets.erase(it);
        } else {
            ++it;
        }
    }
}

void Block::shiftDown(int row)
{
    for (auto& offset : offsets) {
        if (offset.y + start.y < row) {
            // adding to y position of each offset
            offset.y++;
        }
    }
}

// getter for offsets
vector<Position> Block::getOffsets()
{
    return offsets;
}

// printing Block
void Block::printBlock(bool player1)
{
    int maxX = 0;
    int maxY = 0;

    for (Position offset : getOffsets()) {
        maxX = std::max(maxX, offset.x + 1);
        maxY = std::max(maxY, offset.y + 1);
    }

    std::vector<char> blockstr(maxX * maxY, ' ');

    for (Position offset : getOffsets()) {
        blockstr[(offset.y) * maxX + (offset.x)] = c;
    }

    for (int i = 0; i < maxY; i++) {
        if (!player1) {
            std::cout << "\t\t\t";
        }
        for (int j = 0; j < maxX; j++) {
            std::cout << blockstr[i * maxX + j];
        }
        std::cout << std::endl;
    }
}

// clone for block
std::unique_ptr<Block> Block::clone()
{
    Block* b = nullptr;
    // switch case for each specific block
    switch (c) {
    case 'I':
        b = new IBlock();
        break;
    case 'J':
        b = new JBlock();
        break;
    case 'L':
        b = new LBlock();
        break;
    case 'O':
        b = new OBlock();
        break;
    case 'S':
        b = new SBlock();
        break;
    case 'Z':
        b = new ZBlock();
        break;
    case 'T':
        b = new TBlock();
        break;
    }
    b->start = start;
    b->offsets = offsets;
    b->effects = effects;
    b->rotation = rotation;
    b->startingLevel = startingLevel;
    b->c = c;
    return std::unique_ptr<Block>(b);
}
