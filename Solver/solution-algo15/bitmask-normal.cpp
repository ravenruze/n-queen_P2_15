#include <string>
#include <vector>

#include "nqueens.h"

namespace
{

    void search(int row, int n, unsigned full, unsigned cols, unsigned d1, unsigned d2,
                std::vector<int> &placement, std::vector<std::vector<int>> &out)
    {
        if (row == n)
        {
            out.push_back(placement);
            NQ_SNAPSHOT(nq::queensOf(placement), "solution " + std::to_string(out.size()));
            return;
        }

        unsigned avail = full & ~(cols | d1 | d2);
        while (avail)
        {
            unsigned bit = avail & (~avail + 1);
            avail ^= bit;
            placement[row] = __builtin_ctz(bit);
            search(row + 1, n, full, cols | bit, ((d1 | bit) << 1) & full, (d2 | bit) >> 1, placement, out);
        }
    }

}

std::vector<std::vector<int>> solveNQueens(int n)
{
    std::vector<std::vector<int>> out;
    std::vector<int> placement(n, -1);
    search(0, n, (1u << n) - 1, 0, 0, 0, placement, out);
    return out;
}