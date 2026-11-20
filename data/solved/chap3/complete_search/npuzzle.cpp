#include <bits/stdc++.h>
using namespace std;

int main()
{
    char grid[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            char c;
            cin >> c;
            grid[i][j] = c;
        }
        }

    int tot = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            char c = grid[i][j];
            int id = static_cast<int>(c) - 65;
            if (c == '.')
            {
                continue;
            }
            int supposed_row = id / 4;
            int supposed_col = id % 4;
            if (i != supposed_row || supposed_col != j)
            {
                int manh = abs(supposed_row - i) + abs(supposed_col - j);
                tot += manh;
            }
        }
    }
    cout << tot << endl;
}