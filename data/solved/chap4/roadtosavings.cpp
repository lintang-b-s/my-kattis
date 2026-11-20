#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<vector<pair<int, int>>> adjList(n + 1);
    for (int i = 0; i < m; i++)
    {
        int i1, i2, l;
        cin >> i1 >> i2 >> l;

        adjList[i1].push_back({i2, l});
        adjList[i2].push_back({i1, l});
    }

    auto dijkstra = [&](int a, int b)
    {
        unordered_map<int, int> dist;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[a] = 0;
        pq.emplace(0, a);

        while (!pq.empty())
        {
            auto [uDist, u] = pq.top();
            pq.pop();

            if (uDist > dist[u])
            {
                continue;
            }

            if (u == b)
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

        return dist;
    };

    auto distab = dijkstra(a, b);
    auto distba = dijkstra(b, a);

    auto spLength = distab[b];

    int totLengthNotPaved = 0;

    for (int u = 1; u <= n; u++)
    {
        for (auto [v, vDist] : adjList[u])
        {
            if (v < u)
            {
                continue;
            }
            if (!distab.count(v) || !distba.count(v))
            {
                totLengthNotPaved += vDist;
            }
            else if (distab.count(v) && distba.count(v) &&
                     (distab[u] + vDist + distba[v] != spLength) &&
                     (distba[u] + vDist + distab[v] != spLength))
            {
                totLengthNotPaved += vDist;
            }
        }
    }
    cout << totLengthNotPaved << "\n";
}