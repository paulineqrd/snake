#include <vector>
#include "position.hpp"
#pragma once

enum class Direction{
    Up,
    Down,
    Left,
    Right
};

struct Snake
{
    std::vector<Position> body;
    Direction direction;
    int score;
};

