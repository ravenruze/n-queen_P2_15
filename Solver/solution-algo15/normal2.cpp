#include "nqueens.h"
#include <vector>

using namespace std;

vector<vector<int>> solveNQueens(int n) {
    vector<vector<int>> hasil;
    vector<int> posisi(n, -1);

    int mask = (1 << n) - 1;

    auto backtrack = [&](auto&& self, int row,
                         int cols, int diag1, int diag2) -> void {

        if (row == n) {
            hasil.push_back(posisi);
            return;
        }

        int available = mask & ~(cols | diag1 | diag2);

        while (available) {
            int bit = available & -available;
            available -= bit;

            int col = 0;
            while ((1 << col) != bit) {
                col++;
            }

            posisi[row] = col;

            self(self, row + 1,
                 cols | bit,
                 ((diag1 | bit) << 1) & mask,
                 (diag2 | bit) >> 1);

            posisi[row] = -1;
        }
    };

    backtrack(backtrack, 0, 0, 0, 0);

    return hasil;
}