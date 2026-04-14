/* Program name: sudoku.cpp
 * Author: Feda Bigzad
 * Date last updated: 11/24/2025
 * Purpose: Implement the sudoku class: load the grid, solve it using
 *          recursion and backtracking, and print it.
 */

#include "sudoku.h"
#include <fstream>

sudoku::sudoku()
{
    // Initialize grid with zeros.
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            grid[r][c] = 0;
}

bool sudoku::loadGrid(const std::string &fileName)
{
    std::ifstream inFile(fileName);
    if (!inFile)
    {
        std::cerr << "Error: could not open file " << fileName << "\n";
        return false;
    }

    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (!(inFile >> grid[r][c]))
            {
                std::cerr << "Error: not enough values in file.\n";
                return false;
            }
        }
    }

    return true;
}

bool sudoku::solveGrid()
{
    return solve(0, 0);
}

bool sudoku::solve(int row, int col)
{
    // If we have reached row 9, we are past the last row → solved.
    if (row == 9)
        return true;

    // Move to next row if we are past the last column.
    if (col == 9)
        return solve(row + 1, 0);

    // If this cell is already filled, move to the next one.
    if (grid[row][col] != 0)
        return solve(row, col + 1);

    // Try digits 1 through 9.
    for (int num = 1; num <= 9; ++num)
    {
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;

            // Recurse for next cell.
            if (solve(row, col + 1))
                return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }

    // No number works here → backtrack.
    return false;
}

bool sudoku::isSafe(int row, int col, int num) const
{
    return !usedInRow(row, num) &&
           !usedInCol(col, num) &&
           !usedInBox(row - row % 3, col - col % 3, num);
}

bool sudoku::usedInRow(int row, int num) const
{
    for (int c = 0; c < 9; ++c)
        if (grid[row][c] == num)
            return true;
    return false;
}

bool sudoku::usedInCol(int col, int num) const
{
    for (int r = 0; r < 9; ++r)
        if (grid[r][col] == num)
            return true;
    return false;
}

bool sudoku::usedInBox(int boxStartRow, int boxStartCol, int num) const
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (grid[boxStartRow + r][boxStartCol + c] == num)
                return true;
    return false;
}

// Print in the style shown in the assignment sample.
std::ostream &operator<<(std::ostream &os, const sudoku &s)
{
    auto printBorder = [&os]() {
        os << "+-----------+-----------+-----------+\n";
    };

    printBorder();
    for (int r = 0; r < 9; ++r)
    {
        os << "| ";
        for (int c = 0; c < 9; ++c)
        {
            os << s.grid[r][c] << "   ";

            if ((c + 1) % 3 == 0)
                os << "| ";
        }
        os << "\n\n";

        if ((r + 1) % 3 == 0)
            printBorder();
    }

    return os;
}
