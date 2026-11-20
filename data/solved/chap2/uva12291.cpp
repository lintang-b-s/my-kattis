#include <bits/stdc++.h>

using namespace std;

void dfs(int sx, int sy, int lx, int ly,
         vector<vector<char>> small, vector<vector<char>> large, bool &possible,
         bool smallTaken[10][10], bool largeTaken[10][10])
{
    int M = small.size();
    int N = large.size();
    if (sx < 0 || sx >= M || sy < 0 || sy >= M)
        return;

    if (!possible || small[sy][sx] == '.' || smallTaken[sy][sx])
        return;

    if (lx < 0 || lx >= N || ly < 0 || ly >= N || large[ly][lx] == '.' ||
        largeTaken[ly][lx])
    {
        possible = false;
    }

    smallTaken[sy][sx] = true;
    largeTaken[ly][lx] = true;

    dfs(sx - 1, sy, lx - 1, ly, small, large, possible, smallTaken, largeTaken);
    dfs(sx + 1, sy, lx + 1, ly, small, large, possible, smallTaken, largeTaken);
    dfs(sx, sy - 1, lx, ly - 1, small, large, possible, smallTaken, largeTaken);
    dfs(sx, sy + 1, lx, ly + 1, small, large, possible, smallTaken, largeTaken);
}

int main(int argc, char *argv[])
{

    int N, M;
    while (cin >> N >> M)
    {
        if (N == 0 and M == 0)
            break;

        vector<vector<char>> polyomino(N, vector<char>(N));
        int largeCounter = 0, smallCounter = 0;

        for (int i = 0; i < N; i++)
        {
            string row;
            cin >> row;
            for (int j = 0; j < N; j++)
            {
                polyomino[i][j] = row[j];
                if (row[j] == '*')
                    largeCounter++;
            }
        }

        vector<vector<char>> small(M, vector<char>(M));

        vector<pair<int, int>> smallStar;
        for (int i = 0; i < M; i++)
        {
            string row;
            cin >> row;
            for (int j = 0; j < M; j++)
            {
                small[i][j] = row[j];
                if (row[j] == '*')
                {
                    smallCounter++;
                    smallStar.push_back({i, j});
                }
            }
        }

        bool possible = true;

        bool smallTaken[10][10];
        bool polyTaken[10][10];

        pair<int, int> topLeftStarSmall;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (small[i][j] == '*')
                {
                    topLeftStarSmall.first = i;
                    topLeftStarSmall.second = j;
                    i = M;
                    j = M;
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {

                if (polyomino[i][j] == '.')
                    continue;
                possible = true;
                for (int a = 0; a < 10; a++)
                {
                    for (int b = 0; b < 10; b++)
                    {
                        smallTaken[a][b] = false;
                        polyTaken[a][b] = false;
                    }
                }
                dfs(topLeftStarSmall.second, topLeftStarSmall.first,
                    j, i, small, polyomino, possible, smallTaken, polyTaken);

                if (!possible)
                    continue;

                for (int p = 0; p < N; p++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        if (polyomino[p][k] == '.' || polyTaken[p][k])
                            continue;

                        for (int a = 0; a < 10; a++)
                        {
                            for (int b = 0; b < 10; b++)
                            {
                                smallTaken[a][b] = false;
                            }
                        }
                        possible = true;

                        dfs(topLeftStarSmall.second, topLeftStarSmall.first,
                            k, p, small, polyomino, possible, smallTaken, polyTaken);
                        if (!possible)
                            continue;
                        p = N, k = N;
                        i = N, j = N;
                    }
                }
            }
        }

        if (possible)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
    return 0;
}
