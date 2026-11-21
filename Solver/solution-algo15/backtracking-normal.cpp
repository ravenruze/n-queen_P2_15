#include <vector>
#include <cstdlib>
#include <string>

#include "nqueens.h"

void backtrack(int row, int n, std::vector<int>& cols,
               std::vector<std::vector<int>>& solutions) {

    if (row == n) {
        solutions.push_back(cols);

        NQ_SNAPSHOT(
            nq::queensOf(cols),
            "solution " + std::to_string(solutions.size())
        );

        return;
    }

    for (int col = 0; col < n; col++) {

        bool aman = true;

        for (int previousRow = 0; previousRow < row; previousRow++) {
            int previousCol = cols[previousRow];

            if (previousCol == col ||
                std::abs(previousCol - col) == row - previousRow) {
                aman = false;
                break;
            }
        }

        if (aman) {
            cols[row] = col;

            backtrack(row + 1, n, cols, solutions);

            cols[row] = -1;
        }
    }
}

std::vector<std::vector<int>> solveNQueens(int n) {
    std::vector<std::vector<int>> solutions;

    std::vector<int> cols(n, -1);

    backtrack(0, n, cols, solutions);

    return solutions;
}