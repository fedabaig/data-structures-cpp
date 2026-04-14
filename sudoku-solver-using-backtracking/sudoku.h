/* Program name: sudoku.h
 * Author: Feda Bigzad
 * Date last updated: 11/24/2025
 * Purpose: Declare the sudoku class that stores a 9x9 grid, can load it
 *          from a file, solve it using backtracking/recursion, and print it.
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>

class sudoku
{
public:
    sudoku();

    // Load the 9x9 grid from a file (e.g., "sudoku.txt").
    // Zeros represent unknown values.
    bool loadGrid(const std::string &fileName);

    // Solve the grid using recursion and backtracking.
    // Returns true if a solution is found.
    bool solveGrid();

    // Output operator to print the grid in a nice format.
    friend std::ostream &operator<<(std::ostream &os, const sudoku &s);

private:
    int grid[9][9];

    // Recursive helper for solveGrid.
    bool solve(int row, int col);

    // Check if it is safe to put num in grid[row][col].
    bool isSafe(int row, int col, int num) const;

    bool usedInRow(int row, int num) const;
    bool usedInCol(int col, int num) const;
    bool usedInBox(int boxStartRow, int boxStartCol, int num) const;
};

#endif // SUDOKU_H
