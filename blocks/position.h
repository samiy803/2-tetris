#ifndef POSITION_H
#define POSITION_H
struct Position {
    // stores x and y for each pixel of a block
    int x;
    int y;

    //overloaded operator to compare equality of positions
    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};
#endif // !POSITION_H
