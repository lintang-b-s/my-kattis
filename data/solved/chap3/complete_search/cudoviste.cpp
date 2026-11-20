#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r, c;
    cin >> r >> c;
    vector<vector<char>> grid(r, vector<char>(c));

    vector<pair<int, int>> crushedCarsCoords(0);

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            char x;
            cin >> x;
            grid[i][j] = x;
            if (x == 'X')
            {
                crushedCarsCoords.push_back({i, j});
            }
        }
    }

    vector<vector<bool>> gridUsed(r, vector<bool>(c));

    vector<int> res(5);

    for (int row = 0; row < r - 1; row++)
    {
        for (int col = 0; col < c - 1; col++)
        {
            bool building = false;
            int parked = 0;
            for (int dy = 0; dy < 2; dy++)
            {
                for (int dx = 0; dx < 2; dx++)
                {
                    if (grid[row+dy][col+dx] == '#')
                    {
                        building = true;
                    }
                    else if (grid[row+dy][col+dx] == 'X')
                    {
                        parked++;
                    }
                }
            }
            if (!building)
            {
                res[parked]++;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        cout << res[i] << endl;
    }
}