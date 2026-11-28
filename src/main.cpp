#include <chrono>
#include <iostream>
#include <thread>
#include <terminal_ctrl.hpp>
#include "position.hpp"

#include "game.hpp"
#include "render.hpp"

Board menu()
{
    std::cout << "Bienvenue dans le jeu du Snake\nChoisissez la taille du plateau :" << std::endl;
    std::cout << "1. Petit (15x15)\n2. Moyen (20x20)\n3. Grand (30x20)" << std::endl;
    int grid_size{0};
    // FAIRE VERIF POUR ENTREE
    std::cin >> grid_size;

    Board new_board{};
    switch (grid_size)
    {
    case 1:
        new_board = {15, 15};
        break;
    case 2:
        new_board = {20, 20};
        break;
    case 3:
        new_board = {30, 20};
        break;
    default:
        break;
    }

    return (new_board);
};

int main()
{
    Game game{};
    game.board = menu();
    // Active le mode "raw" du terminal sous Linux et MacOS pour lire les touches sans appuyer sur Entrée. Sous Windows, ne fait rien car _getch() lit déjà les touches directement
    // Ce mode raw est automatiquement désactivé à la fin du programme
    terminal_ctrl::RawModeGuard raw_mode{};
    terminal_ctrl::save_default_attributes();

    // Cache le curseur pour éviter les clignotements pendant le redessin.
    terminal_ctrl::set_cursor_visibility(false);

    bool running{true};

    while (running)
    {
        // Efface l'écran et replace le curseur en haut à gauche
        terminal_ctrl::clear_screen();
        terminal_ctrl::set_cursor_position(1, 1);

        std::cout << "Snake\n";
        std::cout << "Appuyez sur Echap pour quitter\n";

        update(game);
        render(game);

        // Vide toutes les touches en attente sans bloquer la boucle de jeu
        while (std::optional<terminal_ctrl::KeyCode> const key{terminal_ctrl::get_key_non_blocking()})
        {
            if (*key == terminal_ctrl::KeyCode::KEY_ESCAPE)
            {
                running = false;
            }
        }

        // Simule une frame avec une pause: ajustez la durée pour changer la vitesse du jeu
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    terminal_ctrl::restore_default_attributes();
    // Restaure le curseur et efface l'écran avant de quitter
    terminal_ctrl::set_cursor_visibility(true);
    terminal_ctrl::clear_screen();
};