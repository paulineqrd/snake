#include "render.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <terminal_ctrl.hpp>

void render(Game const& game)
{
    std::string frame{"Snake\nAppuyez sur Echap pour quitter\n"};

    int const w{game.board.width + 2};
    int const h{game.board.height + 2};
    std::vector<std::string> grid(h, std::string(w, ' '));

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
            {
                grid[i][j] = '#';
            }
        }
    }

    for (std::string const& line : grid)
    {
        frame += line;
        frame += '\n';
    }

    terminal_ctrl::set_cursor_position(1, 1);
    std::cout << frame << std::flush;
}