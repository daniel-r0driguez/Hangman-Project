// Daniel Rodriguez - CS003A
// Two-Player Hangman Game (Due 1/23/2023)
#include "functions.h"
#include <iostream>

std::string getDefaultBoard()
{
    std::string board = "     +---+\n"
                        "     |   |\n"
                        "         |\n"
                        "         |\n"
                        "         |\n"
                        "         |\n"
                        " =========\n";
    return board;
}

void displayMenu()
{
    std::cout << "***********  HANG-MAN  ***********\n"
              << "=================================\n"
              << "|  Mode (Solo or Multiplayer)  |\n"
              << "=================================\n"
              << "(1): Solo     "
              << "(2): Multiplayer\n\n"
              << "Mode: ";
}

int getMode()
{
    int mode = -1;
    do
    {
        try
        {
            mode = std::stoi(getInput());
        }
        catch (std::exception&)
        {
            std::cout << "Invalid option. Please choose either (1) Solo or (2) Multiplayer.\n";
            std::cout << "Mode: ";
        }
        if (mode <= 0 || mode >= 3)
        {
            std::cout << "Invalid option. Please choose either (1) Solo or (2) Multiplayer.\n";
            std::cout << "Mode: ";
        }
    } while(mode <= 0 || mode >= 3); // Bounded to choose between [1 - 2].
    return mode;
}

int setMode(int mode)
{
    if (mode == 1)
    {
        return 1;
    }
    return getPlayers();
}

int getPlayers()
{
    int players = -1;
    std::cout << "How many Players will play?: ";
    do
    {
        try
        {
            players = std::stoi(getInput());
        }
        catch (std::exception&)
        {
            std::cout << "Error! Multiplayer mode requires 2 or more players.\n";
            std::cout << "Players: ";
        }
        if (players <= 1)
        {
            std::cout << "Error! Multiplayer mode requires 2 or more players.\n";
            std::cout << "Players: ";
        }
    } while(players <= 1);
    return players;
}

void getInput(char &letter)
{
    std::cin >> letter;
    letter = tolower(letter);
}

std::string getInput()
{
    std::string input;
    getline(std::cin, input);
    return input;
}

void updateBoard(std::string& board, int misses)
{
    switch(misses)
    {
        case 1:
            board.at(27) = '0';
            break;
        case 2:
            board.at(38) = '|';
            break;
        case 3:
            board.at(37) = '/';
            break;
        case 4:
            board.at(39) = '\\';
            break;
        case 5:
            board.at(48) = '/';
            break;
        case 6:
            board.at(50) = '\\';
            break;
    }
}

void drawBoard(std::string& board)
{
    std::cout << board;
}

bool inWord(const std::string& word, char letter)
{
    // If letter is in string, it will return true. Else it returns false if it is npos (no position).
    return (word.find(letter) != std::string::npos);
}

void prompt (int playerNum)
{
    std::cout << "Enter a letter Player " << playerNum << ": ";
}

std::string getWord(const std::vector<std::string>& words)
{
    return words.at(rand() % words.size());
}

bool loadFromFile(const std::string& filename, std::vector<std::string>& wordBank)
{
    std::ifstream inputFile;
    std::string next;
    if (openFile(inputFile, filename))
    {
        while (getline(inputFile, next))
        {
            wordBank.push_back(next);
        }
        return true;
    }
    else
    {
        std::cout << R"(Missing "words.txt" file! )"
                  << "Cannot start game without this file.\n";
    }
    closeFile(inputFile);
    return false;
}

bool openFile(std::ofstream &out, const std::string& filename)
{
    out.open(filename);
    return !out.fail();
}

bool openFile(std::ifstream& in, const std::string& filename)
{
    in.open(filename);
    return !in.fail();
}

void addWord(const std::string& word, const std::string& filename, std::vector<std::string>& words)
{
    std::ofstream fout;
    if (openFile(fout, filename))
    {
        if (!checkInVec(words, word))
        {
            fout << word << std::endl;
            words.push_back(word);
        }
    }
}

bool checkInVec(const std::vector<std::string>& words, const std::string& word)
{
    // Check if the word is in the vector.
    return std::find(words.cbegin(), words.cend(), word) != words.cend();
}

void closeFile(std::ifstream &in)
{
    in.close();
}

void closeFile(std::ofstream &out)
{
    out.close();
}

void outputLetterbank(const std::vector<char>& letterbank)
{
// Simpler version uses the auto keyword.
    for (auto i : letterbank)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void updateLetterbank(std::vector<char>& letterbank, char guess)
{
    letterbank.push_back(guess);
}

bool checkInVec(std::vector<std::string>& words, const std::string& word)
{
    for (const auto& i : words)
    {
        if (i == word)
        {
            return true;
        }
    }
    return false;
}

void run(int players)
{
    std::cout << "Initializing game...\n";
    // Current player. Always starts with Player 1.
    int curPlayer = 1;
    std::vector<std::string> wordBank;
    if (!loadFromFile("words.txt", wordBank))
        return;
    // Vector of vectors that contain the different letter banks of each player.
    std::vector<std::vector<char>> letterBanks (players, std::vector<char>());
    // Vector of strings which will hold all the different displayWords of each player.
    std::vector<std::string> displayWords (players);
    // Vector of strings which will hold all the real words the players need to solve.
    std::vector<std::string> realWords (players);
    // Vector of strings which will hold each player's individual board.
    std::vector<std::string> boards (players);
    // Vector which will hold each player's individual current misses.
    std::vector<int> misses (players, 0);
    // Input variable
    char input;
    // Set up each player's realWords, displayWords, and boards.
    for (int i = 0; i < players; ++i)
    {
        realWords.at(i) = getWord(wordBank);
        displayWords.at(i) = getDisplayWord(realWords.at(i));
        boards.at(i) = getDefaultBoard();
    }
    // REMOVE
    std::cout << "Game starting\n";
    while(!gameOver(displayWords.at(curPlayer - 1)))
    {
        std::cin.clear();
        drawBoard(boards.at(curPlayer - 1));
        printWord(displayWords.at(curPlayer - 1));
        outputLetterbank(letterBanks.at(curPlayer - 1));
        prompt(curPlayer);
        getInput(input);
        if (!inWord(realWords.at(curPlayer - 1), input))
        {
            misses.at(curPlayer - 1)++;
            // If the current player has reached 6 misses (multiplayer mode only)...
            if (misses.at(curPlayer - 1) >= 6 && players > 1)
            {
                //...announce to players which player was eliminated.
                printEliminated(curPlayer);
            }
            updateBoard(boards.at(curPlayer - 1), misses.at(curPlayer - 1));
            updateLetterbank(letterBanks.at(curPlayer - 1), input);
            // Returns the next player in queue. If (-1) is returned, then that means all players lost.
            curPlayer = chooseNextPlayer(misses, curPlayer);
        }
        else
        {
            updateWord(realWords.at(curPlayer - 1), displayWords.at(curPlayer - 1), input);
        }
        // If no player has less than six misses from the previous turn then...
        if (curPlayer == - 1)
        {
            // ...all players lost, so simply end the game.
            printLost(players);
            return;
        }
    }
    // If the game ends, that means a player has won.
    drawBoard(boards.at(curPlayer - 1));
    printWord(displayWords.at(curPlayer - 1));
    outputLetterbank(letterBanks.at(curPlayer - 1));
    printWinner(curPlayer, players);
}

void printWord(const std::string& word)
{
    for (char i : word)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void updateWord(const std::string& word, std::string& displayWord, char guess)
{
    if(inWord(word, guess))
    {
        for (int i = 0; i < word.size(); i++)
        {
            if (word[i] == guess)
            {
                displayWord[i] = guess;
            }
        }
    }
}

int chooseNextPlayer(const std::vector<int>& misses, int curPlayer)
{
    int maxLoops = 2;
    int start = curPlayer;
    while (maxLoops-- > 0)
    {
        for (int i = start; i < misses.size(); ++i)
        {
            if (misses.at(i) < 6)
            {
                return i + 1;
            }
        }
        start = 0;
    }
    return -1;
}

// Only used in Multiplayer modes
void printEliminated(int playerNum)
{
    std::cout << "__--__--__--___-___-___-___--_--__\n";
    std::cout << "[ Player " << playerNum << " has been eliminated! ]\n";
    std::cout << "--__--__--__--__--__--__--__--__--\n";
}

std::string getDisplayWord(const std::string& word)
{
    std::string displayWord(word.length(), '_');
    word.find('c');
    for (int i = 0; i < word.length(); ++i)
    {
        if (word.at(i) == ' ')
        {
            displayWord.at(i) = ' ';
        }
    }
    return displayWord;
}

bool gameOver(std::string& displayWord)
{
    return (displayWord.find('_') == std::string::npos);
}

void printLost(int players)
{
    if (players == 1)
    {
        std::cout << "________________________\n"
                  << "[ Game Over! You Lost! ]\n"
                  << "------------------------\n";
        return;
    }
    std::cout << "______________________________\n"
              << "[ Game Over! Everybody Lost! ]\n"
              << "------------------------------\n";
}

void printWinner(int playerNum, int players)
{
    if (players == 1)
    {
        std::cout << "=======================================\n";
        std::cout << "|      Congratulations! You win!      |\n";
        std::cout << "=======================================\n";
        return;
    }
    std::cout << "=======================================\n";
    std::cout << "|  Congratulations! Player " << playerNum << " has won! |\n";
    std::cout << "=======================================\n";
}