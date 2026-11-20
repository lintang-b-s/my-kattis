#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{

    int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int cases;
    int kingdomHeir;

    int N, R, C, K;
    while (cin >> N >> R >> C >> K)
    {
        if (N == 0 && R == 0 && C == 0 && K == 0)
        {
            break;
        }
        int kingdom[R][C], newKingdom[R][C];

        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                cin >> kingdomHeir;
                kingdom[i][j] = kingdomHeir;
                newKingdom[i][j] = kingdom[i][j];
            }
        }

        // O(K*R*C)

        for (int battle = 0; battle < K; battle++)
        {
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    int heir = kingdom[i][j];
                    int left = 0, right = 0, above = 0, below = 0;
                    if (i > 0)
                    {
                        above = kingdom[i + step[1][0]][j + step[1][1]];
                        if (above == heir - 1 or (heir == 0 and above == N - 1))
                        {
                            newKingdom[i][j] = above;
                        }
                    }
                    if (j > 0)
                    {
                        left = kingdom[i + step[3][0]][j + step[3][1]];
                        if (left == heir - 1 or (heir == 0 and left == N - 1))
                        {
                            newKingdom[i][j] = left;
                        }
                    }
                    if (j < C - 1)
                    {
                        right = kingdom[i + step[2][0]][j + step[2][1]];
                        if (right == heir - 1 or (heir == 0 and right == N - 1))
                        {
                            newKingdom[i][j] = right;
                        }
                    }
                    if (i < R - 1)
                    {
                        below = kingdom[i + step[0][0]][j + step[0][1]];
                        if (below == heir - 1 or (heir == 0 and below == N - 1))
                        {
                            newKingdom[i][j] = below;
                        }
                    }
                }
            }

            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    kingdom[i][j] = newKingdom[i][j];
                }
            }
        }

        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if (j > 0)
                {
                    cout << " ";
                }

                cout << newKingdom[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}
