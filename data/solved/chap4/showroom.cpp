#include <bits/stdc++.h>
using namespace std;

const int INF_WEIGHT = 1e7;

int main()
{
    int r, c;

    cin >> r >> c;

    vector<vector<char>> grid(r, vector<char>(c, ' '));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> grid[i][j];
        }
    }

    vector<vector<pair<int, int>>> adjList(r * c);

    auto cellToNId = [&](int i, int j) -> int
    {
        return i * c + j;
    };

    auto getWeight = [&](int i, int j) -> int
    {
        if (grid[i][j] == 'c')
        {
            return 1;
        }
        else if (grid[i][j] == 'D')
        {
            return 0;
        }
        return INF_WEIGHT;
    };

    vector<pair<int, int>> pintuUjungs(0);

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (j + 1 < c)
            {
                int weight = getWeight(i, j + 1);

                adjList[cellToNId(i, j)].push_back({cellToNId(i, j + 1), weight});
            }
            if (i + 1 < r)
            {
                int weight = getWeight(i + 1, j);

                adjList[cellToNId(i, j)].push_back({cellToNId(i + 1, j), weight});
            }

            if (j - 1 >= 0)
            {
                int weight = getWeight(i, j - 1);

                adjList[cellToNId(i, j)].push_back({cellToNId(i, j - 1), weight});
            }

            if (i - 1 >= 0)
            {
                int weight = getWeight(i - 1, j);

                adjList[cellToNId(i, j)].push_back({cellToNId(i - 1, j), weight});
            }

            if (j == c - 1 && grid[i][j] == 'D')
            {
                pintuUjungs.push_back({i, j});
            }

            if (j == 0 && grid[i][j] == 'D')
            {
                pintuUjungs.push_back({i, j});
            }

            if (i == 0 && grid[i][j] == 'D')
            {
                pintuUjungs.push_back({i, j});
            }

            if (i == r - 1 && grid[i][j] == 'D')
            {
                pintuUjungs.push_back({i, j});
            }
        }
    }

    unordered_map<int, int> dist;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (auto p : pintuUjungs)
    {
        dist[cellToNId(p.first, p.second)] = 0;
        pq.emplace(0, cellToNId(p.first, p.second));
    }

    int tx, ty;
    cin >> tx >> ty;
    tx--;
    ty--;
    int tnId = cellToNId(tx, ty);

    while (!pq.empty())
    { 
        auto [uDist, u] = pq.top();
        pq.pop();

        if (dist.count(u) && uDist > dist[u])
        {
            continue;
        }
        if (u == tnId)
        {
            break;
        }

        for (auto [v, vDist] : adjList[u])
        {
            if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
            {
                dist[v] = uDist + vDist;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << dist[tnId];
}