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

    auto upperBound = [&](const vector<int>& cand) {

        vector<vector<int>> groups;

        for (int v : cand) {

            bool placed = false;

            for (auto& group : groups) {

                bool joins = true;

                for (int u : group) {
                    if (!conflict[v][u]) {
                        joins = false;
                        break;
                    }
                }

                if (joins) {
                    group.push_back(v);
                    placed = true;
                    break;
                }
            }

            if (!placed)
                groups.push_back({v});
        }

        return (int)groups.size();
    };

    function<void(vector<int>)> dfs =
        [&](vector<int> cand) {

        if ((int)chosen.size() +
            upperBound(cand) < best)
            return;

        if (cand.empty()) {

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

        int v = cand.front();

        vector<int> includeCand;
        vector<int> excludeCand;

        for (int id : cand) {

            if (id == v) continue;

            excludeCand.push_back(id);

            if (!conflict[v][id])
                includeCand.push_back(id);
        }

        chosen.push_back(v);
        dfs(includeCand);
        chosen.pop_back();

        dfs(excludeCand);
    };

    vector<int> all(m);

    for (int i = 0; i < m; i++)
        all[i] = i;

    dfs(all);

    return ans;
}