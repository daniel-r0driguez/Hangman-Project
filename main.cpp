// Daniel Rodriguez - CS003A
// Two-Player Hangman Game
#include "functions.h"
#include <iostream>

int main()
{
    char ans;
    int players;
    int mode;
    displayMenu();
    mode = getMode();
    players = setMode(mode);
    do
    {
        std::cout << "Running game...\n";
        run(players);
        std::cout << "Play again? (Y/N): ";
        std::cin >> ans;
    } while (ans == 'Y' || ans == 'y');
    return 0;
}