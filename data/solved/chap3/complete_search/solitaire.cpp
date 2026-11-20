#include <bits/stdc++.h>
using namespace std;




void backtrack(char grid[5][9], int peg_count, int &max_peg_count)
{
    max_peg_count = max(max_peg_count, peg_count);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 'o')
            {
                if (i + 2 < 5 && grid[i + 1][j] == 'o' && grid[i + 2][j] == '.')
                {
                    grid[i][j] = '.';
                    grid[i + 1][j] = '.';
                    grid[i + 2][j] = 'o';
                    backtrack(grid, peg_count + 1, max_peg_count);
                    grid[i + 1][j] = 'o';
                    grid[i + 2][j] = '.';
                    grid[i][j] = 'o';
                }
                if (j + 2 < 9 && grid[i][j + 1] == 'o' && grid[i][j + 2] == '.')
                {
                    grid[i][j] = '.';
                    grid[i][j + 1] = '.';
                    grid[i][j + 2] = 'o';
                    backtrack(grid, peg_count + 1, max_peg_count);
                    grid[i][j + 1] = 'o';
                    grid[i][j + 2] = '.';
                    grid[i][j] = 'o';
                }
                if (i - 2 >= 0 && grid[i - 1][j] == 'o' && grid[i - 2][j] == '.')
                {

                    grid[i][j] = '.';
                    grid[i - 1][j] = '.';
                    grid[i - 2][j] = 'o';
                    backtrack(grid, peg_count + 1, max_peg_count);
                    grid[i - 1][j] = 'o';
                    grid[i - 2][j] = '.';
                    grid[i][j] = 'o';
                }
                if (j - 2 >= 0 && grid[i][j - 1] == 'o' && grid[i][j - 2] == '.')
                {
                    grid[i][j] = '.';
                    grid[i][j - 1] = '.';
                    grid[i][j - 2] = 'o';
                    backtrack(grid, peg_count + 1, max_peg_count);
                    grid[i][j - 1] = 'o';
                    grid[i][j - 2] = '.';
                    grid[i][j] = 'o';
                }
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int t = 0; t < n; t++)
    {
        char grid[5][9];
        vector<pair<int, int>> pegs;
        int peg_count = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == 'o')
                {
                    peg_count++;
                    pegs.push_back({i, j});
                }
            }
        }

        int max_peg_count = 0;
        backtrack(grid, 0, max_peg_count);
        cout << peg_count - max_peg_count << " " << max_peg_count << endl;
    }
}

// wa
// void backtrack(char(grid)[5][9], int i, int j, int k, int peg_count, int &min_steps, int step, int &min_pegs, vector<pair<int, int>> pegs,
//                vector<bool> used_pegs)
// {

// bool can = false;

// if (i + 2 < 5 && grid[i + 1][j] == 'o' && grid[i + 2][j] == '.')
// {
//     pegs[k] = {i + 2, j};
//     grid[i][j] = '.';
//     grid[i + 1][j] = '.';
//     grid[i + 2][j] = 'o';
//     backtrack(grid, i + 2, j, k, peg_count - 1, min_steps, step + 1, min_pegs, pegs, used_pegs);
//     grid[i + 1][j] = 'o';
//     grid[i + 2][j] = '.';
//     grid[i][j] = 'o';
//     pegs[k] = {i, j};
//     can = true;
// }
// if (j + 2 < 9 && grid[i][j + 1] == 'o' && grid[i][j + 2] == '.')
// {
//     pegs[k] = {i, j + 2};
//     grid[i][j] = '.';
//     grid[i][j + 1] = '.';
//     grid[i][j + 2] = 'o';
//     backtrack(grid, i, j + 2, k, peg_count - 1, min_steps, step + 1, min_pegs, pegs, used_pegs);
//     grid[i][j + 1] = 'o';
//     grid[i][j + 2] = '.';
//     grid[i][j] = 'o';
//     pegs[k] = {i, j};
//     can = true;
// }
// if (i - 2 >= 0 && grid[i - 1][j] == 'o' && grid[i - 2][j] == '.')
// {
//     pegs[k] = {i - 2, j};

//     grid[i][j] = '.';
//     grid[i - 1][j] = '.';
//     grid[i - 2][j] = 'o';
//     backtrack(grid, i - 2, j, k, peg_count - 1, min_steps, step + 1, min_pegs, pegs, used_pegs);
//     grid[i - 1][j] = 'o';
//     grid[i - 2][j] = '.';
//     grid[i][j] = 'o';
//     pegs[k] = {i, j};
//     can = true;
// }
// if (j - 2 >= 0 && grid[i][j - 1] == 'o' && grid[i][j - 2] == '.')
// {
//     pegs[k] = {i, j - 2};
//     grid[i][j] = '.';
//     grid[i][j - 1] = '.';
//     grid[i][j - 2] = 'o';
//     backtrack(grid, i, j - 2, k, peg_count - 1, min_steps, step + 1, min_pegs, pegs, used_pegs);
//     grid[i][j - 1] = 'o';
//     grid[i][j - 2] = '.';
//     grid[i][j] = 'o';
//     pegs[k] = {i, j};
//     can = true;
// }

//     for (int q = 0; q < pegs.size(); q++)
//     {
//         if (!used_pegs[q] && grid[pegs[q].first][pegs[q].second] == 'o')
//         {
//             can = true;
//             used_pegs[q] = true;
//             backtrack(grid, pegs[q].first, pegs[q].second, q, peg_count, min_steps, step, min_pegs, pegs, used_pegs);
//             used_pegs[q] = false;
//         }
//     }

//     if (!can)
//     {
//         if (peg_count < min_pegs)
//         {
//             min_pegs = peg_count;
//             min_steps = step;
//         }
//         else if (peg_count == min_pegs)
//         {
//             min_steps = min(min_steps, step);
//         }
//     }

//     used_pegs[k] = false;
// }

// int main()
// {
//     int n;
//     cin >> n;
//     for (int t = 0; t < n; t++)
//     {
//         char grid[5][9];
//         int peg_count = 0;
//         vector<pair<int, int>> pegs;
//         for (int i = 0; i < 5; i++)
//         {
//             for (int j = 0; j < 9; j++)
//             {
//                 cin >> grid[i][j];
//                 if (grid[i][j] == 'o')
//                 {
//                     peg_count++;
//                     pegs.push_back({i, j});
//                 }
//             }
//         }

//         int min_steps = numeric_limits<int>::max();
//         vector<bool> used_pegs(peg_count, false);
//         int min_pegs = numeric_limits<int>::max();

//         used_pegs[0] = true;
//         backtrack(grid, pegs[0].first, pegs[0].second, 0, peg_count, min_steps, 0, min_pegs, pegs, used_pegs);
//         cout << peg_count - min_steps << " " << min_steps << endl;
//     }
// }
