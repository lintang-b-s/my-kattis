#include <bits/stdc++.h>
using namespace std;

// ub 4^5 with pruning. backtracking recursion tree with 4 children node (cuma bisa ke key yang sama/kanan/bawah/diagonal kanan bawah) dengan height=5.
void backtrack(int i, char numpad[10], int col[10], int row[10], vector<int> &numbers, string key)
{
    if (key.size() <= 4 && key.size() > 0 && key != "")
    {
        int keynum = stoi(key);
        if (keynum <= 200 && keynum >= 1)
        {
            numbers.push_back(keynum);
        }
    }
    if (key.size() > 4)
    {
        return;
    }

    for (int j = 0; j < 10; j++)
    {
        if (j < i || col[j] < col[i] || row[j] < row[i])
        {
            continue;
        }

        backtrack(j, numpad, col, row, numbers, key + numpad[j]);
    }
}

int main()
{
    int t;
    cin >> t;
    char numpad[10];
    int col[10], row[10];
    int grid[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[i][j] = (i * 3 + j) + 1;
            numpad[i * 3 + j] = ((i * 3 + j) + 1) + '0';
            col[i * 3 + j] = j;
            row[i * 3 + j] = i;
        }
    }

    numpad[9] = 0 + '0';
    col[9] = 1;
    row[9] = 3;

    for (int i = 0; i < t; i++)
    {
        int k;
        cin >> k;

        vector<int> angkas;

        backtrack(0, numpad, col, row, angkas, "");

        int maxdist = numeric_limits<int>::max();
        int best = angkas[0];
        for (auto c : angkas)
        {

            if (abs(c - k) < abs(best - k))
            {
                best = c;
                maxdist = c - k;
            }
        }
        cout << best << endl;
    }
}

// WA
// void backtrack(int r, int j, vector<int> &numbers, int angka, int grid[3][3],
//                int last)
// {
//     if (r == 3)
//     {
//         if (last == 8)
//         {
//             angka *= 10;
//         }
//         numbers.push_back(angka);
//         return;
//     }

//     for (int i = j; i < 3; i++)
//     {
//         angka *= 10;
//         angka += grid[r][i];
//         if (angka > 200)
//         {
//             angka -= grid[r][i];
//             angka /= 10;
//             continue;
//         }
//         backtrack(r + 1, i, numbers, angka, grid, grid[r][i]);
//         angka -= grid[r][i];
//         angka /= 10;
//     }
// }

// int main()
// {
//     int t;
//     cin >> t;
//     int grid[3][3];
//     for (int i = 0; i < 3; i++)
//     {
//         for (int j = 0; j < 3; j++)
//         {
//             grid[i][j] = (i * 3 + j) + 1;
//         }
//     }

//     for (int i = 0; i < t; i++)
//     {
//         int k;
//         cin >> k;

//         vector<int> angkas;

//         for (int r = 0; r < 3; r++)
//         {
//             backtrack(r, 0, angkas, 0, grid, 0);
//         }

//         int maxdist = numeric_limits<int>::max();
//         int best = angkas[0];
//         for (auto c : angkas)
//         {
//             if (abs(c - k) < abs(best - k))
//             {
//                 best = c;
//                 maxdist = c - k;
//             }
//         }
//         cout << best << endl;
//     }
// }