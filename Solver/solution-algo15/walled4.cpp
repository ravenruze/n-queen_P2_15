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

vector<vector<pair<int,int>>> solveWalled(
    int n, const vector<string>& grid) {

    vector<Cell> cells;
    vector<vector<int>> segments;

    vector<vector<int>> id(
        n, vector<int>(n, -1));

    for (int r = 0; r < n; r++) {

        for (int c = 0; c < n; c++) {

            if (grid[r][c] != 'W') {
                id[r][c] = cells.size();
                cells.push_back({r,c});
            }
        }
    }

    int m = cells.size();

    for (int r = 0; r < n; r++) {

        int c = 0;

        while (c < n) {

            while (c < n && grid[r][c] == 'W')
                c++;

            vector<int> segment;

            while (c < n && grid[r][c] != 'W') {
                segment.push_back(id[r][c]);
                c++;
            }

            if (!segment.empty())
                segments.push_back(segment);
        }
    }

    vector<vector<bool>> conflict(
        m, vector<bool>(m, false));

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {

            int dr = cells[j].r - cells[i].r;
            int dc = cells[j].c - cells[i].c;

            if (!(dr == 0 || dc == 0 ||
                  abs(dr) == abs(dc)))
                continue;

            int sr = (dr > 0) - (dr < 0);
            int sc = (dc > 0) - (dc < 0);

            int r = cells[i].r + sr;
            int c = cells[i].c + sc;

            bool wall = false;

            while (r != cells[j].r ||
                   c != cells[j].c) {

                if (grid[r][c] == 'W') {
                    wall = true;
                    break;
                }

                r += sr;
                c += sc;
            }

            if (!wall)
                conflict[i][j] = conflict[j][i] = true;
        }
    }

    vector<int> chosen;
    vector<vector<pair<int,int>>> ans;

    int best = -1;
    int total = segments.size();

    function<void(int)> dfs = [&](int s) {

        if ((int)chosen.size() + total - s < best)
            return;

        if (s == total) {

            int count = chosen.size();

            if (count > best) {
                best = count;
                ans.clear();
            }

            if (count == best) {

                vector<pair<int,int>> board;

                for (int x : chosen)
                    board.push_back({
                        cells[x].r,
                        cells[x].c
                    });

                ans.push_back(board);
            }

            return;
        }

        // Tidak menempatkan ratu pada segmen ini.
        dfs(s + 1);

        // Mencoba setiap posisi dalam segmen.
        for (int v : segments[s]) {

            bool valid = true;

            for (int x : chosen) {
                if (conflict[v][x]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                chosen.push_back(v);
                dfs(s + 1);
                chosen.pop_back();
            }
        }
    };

    dfs(0);

    return ans;
}