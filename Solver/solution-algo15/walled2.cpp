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

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c] != 'W')
                cells.push_back({r,c});

    int m = cells.size();

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

            bool blocked = false;

            while (r != cells[j].r ||
                   c != cells[j].c) {

                if (grid[r][c] == 'W') {
                    blocked = true;
                    break;
                }

                r += sr;
                c += sc;
            }

            if (!blocked)
                conflict[i][j] = conflict[j][i] = true;
        }
    }

    vector<int> chosen;
    vector<vector<pair<int,int>>> ans;
    int best = -1;

    function<void(vector<int>)> dfs =
        [&](vector<int> candidates) {

        if ((int)chosen.size() +
            (int)candidates.size() < best)
            return;

        if (candidates.empty()) {

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

        int pick = 0;
        int maxDegree = -1;

        for (int i = 0; i < (int)candidates.size(); i++) {

            int degree = 0;

            for (int j = 0; j < (int)candidates.size(); j++) {
                if (i != j &&
                    conflict[candidates[i]][candidates[j]])
                    degree++;
            }

            if (degree > maxDegree) {
                maxDegree = degree;
                pick = i;
            }
        }

        int v = candidates[pick];

        vector<int> withoutV;
        vector<int> withV;

        for (int id : candidates) {
            if (id == v) continue;

            withoutV.push_back(id);

            if (!conflict[v][id])
                withV.push_back(id);
        }

        chosen.push_back(v);
        dfs(withV);
        chosen.pop_back();

        dfs(withoutV);
    };

    vector<int> all(m);

    for (int i = 0; i < m; i++)
        all[i] = i;

    dfs(all);

    return ans;
}