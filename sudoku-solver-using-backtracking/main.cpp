/* Program name: main.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/24/2025
 * Purpose: Create a sudoku object, load the starting grid from sudoku.txt,
 *          print the starting grid, solve it using backtracking, and print
 *          the solved grid.
 */

#include <iostream>
#include "sudoku.h"

int main()
{
    sudoku puzzle;

    if (!puzzle.loadGrid("sudoku.txt"))
    {
        std::cerr << "Failed to load sudoku.txt\n";
        return 1;
    }

    std::cout << "Starting Sudoku:\n";
    std::cout << puzzle << "\n";

    if (puzzle.solveGrid())
    {
        std::cout << "Solved Sudoku:\n";
        std::cout << puzzle << "\n";
    }
    else
    {
        std::cout << "No solution found for this Sudoku.\n";
    }

    return 0;
}
