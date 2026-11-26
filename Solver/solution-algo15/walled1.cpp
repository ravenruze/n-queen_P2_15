#include "nqueens.h"
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <cstdlib>

using namespace std;

struct Cell {
    int r, c;
};

bool blocked(const vector<string>& grid, Cell a, Cell b) {
    int dr = (b.r > a.r) - (b.r < a.r);
    int dc = (b.c > a.c) - (b.c < a.c);

    int r = a.r + dr;
    int c = a.c + dc;

    while (r != b.r || c != b.c) {
        if (grid[r][c] == 'W') return true;
        r += dr;
        c += dc;
    }
    return false;
}

vector<vector<pair<int,int>>> solveWalled(
    int n, const vector<string>& grid) {

    vector<Cell> cells;

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c] != 'W')
                cells.push_back({r,c});

    int m = cells.size();

    vector<int> chosen;
    vector<vector<pair<int,int>>> ans;

    int best = -1;

    function<void(int)> dfs = [&](int pos) {

        if ((int)chosen.size() + m - pos < best)
            return;

        if (pos == m) {
            int count = chosen.size();

            if (count > best) {
                best = count;
                ans.clear();
            }

            if (count == best) {
                vector<pair<int,int>> board;

                for (int id : chosen)
                    board.push_back({
                        cells[id].r,
                        cells[id].c
                    });

                ans.push_back(board);
            }
            return;
        }

        bool valid = true;

        for (int id : chosen) {
            int dr = abs(cells[pos].r - cells[id].r);
            int dc = abs(cells[pos].c - cells[id].c);

            if ((dr == 0 || dc == 0 || dr == dc) &&
                !blocked(grid, cells[pos], cells[id])) {
                valid = false;
                break;
            }
        }

        if (valid) {
            chosen.push_back(pos);
            dfs(pos + 1);
            chosen.pop_back();
        }

        dfs(pos + 1);
    };

    dfs(0);

    return ans;
}