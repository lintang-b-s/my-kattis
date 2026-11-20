#include <bits/stdc++.h>
using namespace std;
// AC

pair<int, int> possible_moves[4] = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

// ub 4^16. there are only max 16 possible black pieces can be captured..
// backtracking recursion tree 4 children nodes each node with height number of max black pieces can be captured=16.
// pruning gak ngaruh ke upper bound nya
void backtrack(int r, int c, char grid[10][10], int cap, int &maxCap)
{
    maxCap = max(maxCap, cap);
    if (r >= 10 || c >= 10 || c < 0 || r < 0)
    {
        return;
    }

    for (auto move : possible_moves)
    {
        if (r + 2 * move.first < 10 && r + 2 * move.first >= 0 && c + 2 * move.second < 10 &&
            c + 2 * move.second >= 0 && grid[r + move.first][c + move.second] == 'B' &&
            grid[r + 2 * move.first][c + 2 * move.second] == '#')
        {
            grid[r + move.first][c + move.second] = '#';
            backtrack(r + 2 * move.first, c + 2 * move.second, grid, cap + 1, maxCap);
            grid[r + move.first][c + move.second] = 'B';
        }
    }
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        char grid[10][10];
        vector<pair<int, int>> light_pos;

        for (int r = 0; r < 10; r++)
        {
            for (int c = 0; c < 10; c++)
            {
                char cell;
                cin >> cell;
                grid[r][c] = cell;
                if (cell == 'W')
                {
                    light_pos.push_back({r, c});
                }
            }
        }

        int maxcapall = 0;
        for (auto lp : light_pos)
        {
            int maxcap = 0;
            int cap = 0;
            grid[lp.first][lp.second] = '#';
            backtrack(lp.first, lp.second, grid, cap, maxcap);
            grid[lp.first][lp.second] = 'W';
            maxcapall = max(maxcapall, maxcap);
        }
        cout << maxcapall << endl;
    }
}
