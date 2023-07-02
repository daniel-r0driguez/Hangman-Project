// Daniel Rodriguez - CS003A
// Two-Player Hangman Game (Due 1/23/2023)
#ifndef CS003A_FUNCTIONS_H
#define CS003A_FUNCTIONS_H
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// Returns an empty, default hang-man board.
std::string getDefaultBoard();
// Displays the hang-man menu.
void displayMenu();
// Ask and return which mode the user would like to play (either 1 or 2).
int getMode();
// Set the mode.
int setMode(int mode);
// Acquire the amount of players that will play.
int getPlayers();
// Get input from user.
void getInput(char &letter);
// Get input from user. Returns a string copy of the input.
std::string getInput();
// Update the hang-man board.
void updateBoard(std::string& board, int misses);
// Draw the hang-man board.
void drawBoard(std::string& board);
// Check if the user's input character is in the word.
bool inWord(const std::string& word, char letter);
// Unused prompt function.
void prompt(const std::string& message);
// Prompt the current player.
void prompt(int playerNum);
// Get random word from a string vector.
std::string getWord(const std::vector <std::string>& words);
// Returns the dash form of the word.
// Example std::string word = "dashing fast". Function would return "_ _ _ _ _ _ _  _ _ _ _".
std::string getDisplayWord(const std::string& word);
// Load words from file
bool loadFromFile(const std::string& filename, std::vector<std::string>& wordBank);
// Open a file for output. Returns false if file cannot open.
bool openFile(std::ofstream& out, const std::string& filename);
// Open a file for input. Returns false if file cannot open.
bool openFile(std::ifstream& in, const std::string& filename);
// Add word to file
void addWord(const std::string& word, const std::string& filename, std::vector<std::string>& words);
// Close output file
void closeFile(std::ofstream& out);
// Close input file
void closeFile(std::ifstream& in);
// output letterbank
void outputLetterbank(const std::vector<char>& letterbank);
// update letterbank
void updateLetterbank(std::vector<char>& letterbank, char guess);
bool checkInVec(std::vector<std::string>& words, const std::string& word);
// Run the game
void run(int players);
// Primarily used to print the displayWord.
void printWord(const std::string& word);
// Update the displayWord when a guess is right.
void updateWord(const std::string& word, std::string& displayWord, char guess);
// Returns an integer representing which player's turn it is. If all players are eliminated, returns -1.
int chooseNextPlayer(const std::vector<int>& misses, int curPlayer);
// Announces the elimination of a Player when they get 6 misses.
void printEliminated(int playerNum);
// Constantly checks to see if a player's displayWord has been solved. If solved, returns true.
bool gameOver(std::string& displayWord);
// Announces that all players have lost.
void printLost(int players);
// Announces which player has won the game.
void printWinner(int playerNum, int players);
#endif //CS003A_FUNCTIONS_H