#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/hopscotch50?tab=metadata

typedef unsigned long long ull;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> grid(n, vector<int>(n, 0));

    unordered_map<int, vector<pair<int, int>>> tilePos;
    unordered_map<int, int> coordToTile;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
            tilePos[grid[i][j]].push_back(make_pair(i, j));
            coordToTile[i | (j << 15)] = grid[i][j];
        }
    }
    int minDist = INT_MAX;

    for (auto [sx, sy] : tilePos[1])
    {
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.emplace(0, make_pair(sx, sy));
        unordered_map<int, int> dist;

        dist[sx | (sy << 15)] = 0;

        while (!pq.empty())
        { // O((m+n) log n), m =jumlah edges dari graph, n = jumlah node/tile
            // worst case ketika graph is complete graph Kn, dengan m= n(n-1)/2
            // worst case complete graph:  O((n(n-1)/2 + n ) log n)
            auto [uDist, uCoord] = pq.top();
            auto [ux, uy] = uCoord;
            int ukey = ux | (uy << 15);
            int u = coordToTile[ukey];

            pq.pop();

            if (dist.count(ukey) && uDist > dist[ukey])
            {
                continue;
            }

            for (auto [x, y] : tilePos[u + 1])
            {
                int vkey = x | (y << 15);
                int v = coordToTile[vkey];
                int manhattan = abs(ux - x) + abs(uy - y);
                if (!dist.count(vkey) || (dist.count(vkey) && dist[ukey] + manhattan < dist[vkey]))
                {
                    dist[vkey] = dist[ukey] + manhattan;
                    pq.emplace(dist[vkey], make_pair(x, y));
                }
            }
        }

        for (auto [tx, ty] : tilePos[k])
        {
            int tkey = tx | (ty << 15);
            if (dist.count(tkey))
            {
                minDist = min(dist[tkey], minDist);
            }
        }
    }

    if (minDist != INT_MAX)
    {
        cout << minDist << "\n";
        return 0;
    }
    cout << -1 << "\n";

    return 0;
}

// WA
// int main()
// {
//     int n, k;
//     cin >> n >> k;
//     vector<vector<int>> grid(n, vector<int>(n, 0));

//     unordered_map<int, vector<pair<int, int>>> tilePos;
//     unordered_map<int, int> coordToTile;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cin >> grid[i][j];
//             tilePos[grid[i][j]].push_back(make_pair(i, j));
//             coordToTile[i | (j << 15)] = grid[i][j];
//         }
//     }
//     int minDist = INT_MAX;

//     for (auto [sx, sy] : tilePos[1])
//     { // O(n^2 * log n)
//         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
//         pq.emplace(0, make_pair(sx, sy));
//         unordered_map<int, int> dist;

//         dist[1] = 0;

//         while (!pq.empty())
//         {
//             auto [uDist, uCoord] = pq.top();
//             auto [ux, uy] = uCoord;
//             int u = coordToTile[ux | (uy << 15)];

//             pq.pop();

//             if (uDist > dist[u])
//             {
//                 continue;
//             }

//             for (auto [x, y] : tilePos[u + 1])
//             {
//                 int v = coordToTile[x | (y << 15)];
//                 int manhattan = abs(ux - x) + abs(uy - y);
//                 if (!dist.count(v) || (dist.count(v) && dist[u] + manhattan < dist[v]))
//                 {
//                     dist[v] = dist[u] + manhattan;
//                     pq.emplace(dist[v], make_pair(x, y));
//                 }
//             }
//         }
//         if (dist.count(k))
//         {
//             minDist = min(dist[k], minDist);
//         }
//     }

//     if (minDist != INT_MAX)
//     {
//         cout << minDist << "\n";
//         return 0;
//     }
//     cout << -1 << "\n";

//     return 0;
// }