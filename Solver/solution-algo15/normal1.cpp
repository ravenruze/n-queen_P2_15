#include "nqueens.h"
#include <vector>
#include <functional>

using namespace std;

vector<vector<int>> solveNQueens(int n) {
    vector<vector<int>> hasil;
    vector<int> posisi(n, -1);

    vector<bool> kolom(n, false);
    vector<bool> diagonal1(2 * n - 1, false);
    vector<bool> diagonal2(2 * n - 1, false);

    function<void(int)> backtrack = [&](int baris) {
        if (baris == n) {
            hasil.push_back(posisi);
            return;
        }

        for (int c = 0; c < n; c++) {
            int d1 = baris - c + n - 1;
            int d2 = baris + c;

            if (!kolom[c] && !diagonal1[d1] && !diagonal2[d2]) {
                posisi[baris] = c;

                kolom[c] = true;
                diagonal1[d1] = true;
                diagonal2[d2] = true;

                backtrack(baris + 1);

                kolom[c] = false;
                diagonal1[d1] = false;
                diagonal2[d2] = false;

                posisi[baris] = -1;
            }
        }
    };

    backtrack(0);

    return hasil;
}