#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

// https://open.kattis.com/problems/george?tab=metadata

int main()
{
    int n, m;
    cin >> n >> m;
    int a, b, k, g;
    cin >> a >> b >> k >> g;

    vector<int> georgeStreets(0);

    int prevg = -1;
    for (int i = 0; i < g; i++)
    {
        int g1;
        cin >> g1;
        georgeStreets.push_back(g1);
    }

    vector<vector<pair<int, int>>> adjList(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    int time = 0;
    unordered_map<ull, pair<int, int>> blockedStreets;
    for (int i = 0; i < g - 1; i++)
    {
        int g1 = georgeStreets[i];
        int g2 = georgeStreets[i + 1];
        ull key = (ull)g1 | ((ull)g2 << 15);
        ull key2 = (ull)g2 | ((ull)g1 << 15);

        int w = 0;
        for (auto [v, vw] : adjList[g1])
        {
            if (v == g2)
            {
                w = vw;
            }
        }

        blockedStreets[key] = make_pair(time, time + w - 1);
        blockedStreets[key2] = make_pair(time, time + w - 1);

        time += w;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, int> dist;

    dist[a] = k;
    pq.emplace(k, a);

    while (!pq.empty())
    { // O((m+n) log n)
        auto [utime, u] = pq.top();
        pq.pop();

        if (utime > dist[u])
        {
            continue;
        }

        for (auto [v, vw] : adjList[u])
        {
            ull key = (ull)u | ((ull)v << 15);
            int distv = dist[u];
            if (blockedStreets.count(key) && utime <= blockedStreets[key].second && utime >= blockedStreets[key].first)
            {
                distv += (blockedStreets[key].second + 1) - utime;
            }
            if (!dist.count(v) || (dist.count(v) && distv + vw < dist[v]))
            {
                dist[v] = distv + vw;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << dist[b] - k << "\n";
}