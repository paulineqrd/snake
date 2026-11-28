#pragma once
#include "snake.hpp"

struct Board
{
    int width{0};
    int height{0};
};

struct Game
{
    Board board{};
    Snake snake{};
    bool running{true};
};

void update(Game& game);