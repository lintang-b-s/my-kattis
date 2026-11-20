#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{

    int grid[3][3];
    int gridh[3][3];
    int temp[3][3];
    int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int cases;
    char digit;

    cin >> cases;
    for (int c = 0; c < cases; c++)
    {
        int hcnt = 0;
        int cntZero = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> digit;
                grid[i][j] = digit - '0';
                gridh[i][j] = grid[i][j];
                temp[i][j] = gridh[i][j];
                if (gridh[i][j] == 0)
                {
                    cntZero++;
                }
            }
        }

        if (cntZero == 9)
        {
            cout << -1 << endl;
        }
        else
        {
            
            while (true)
            {
                // O(N*M)

                int cntZero = 0;
                hcnt++;

                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        int left = 0, top = 0, right = 0, below = 0;

                        if (i > 0)
                        {
                            top = temp[i + step[1][0]][j + step[1][1]];
                        }
                        if (j > 0)
                        {
                            left = temp[i + step[3][0]][j + step[3][1]];
                        }
                        if (j < 2)
                        {
                            right = temp[i + step[2][0]][j + step[2][1]];
                        }
                        if (i < 2)
                        {
                            below = temp[i + step[0][0]][j + step[0][1]];
                        }
                        gridh[i][j] = (left + top + right + below) % 2;
                        if (gridh[i][j] == 0)
                        {
                            cntZero++;
                        }
                    }
                }

                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        temp[i][j] = gridh[i][j];

                if (cntZero == 9)
                {
                    break;
                }
            }

            cout << hcnt - 1 << endl;

            memset(gridh, 0, sizeof(gridh));
        }
    }

    return 0;
}