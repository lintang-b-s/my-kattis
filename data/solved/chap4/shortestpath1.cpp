#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/shortestpath1?tab=metadata
int main()
{
    int n, m, q, s;

    while (cin >> n >> m >> q >> s)
    {
        vector<vector<pair<int, int>>> adjList(n);

        if (n == 0 && m == 0 && q == 0 && s == 0)
        {
            break;
        }
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            adjList[u].push_back({v, w});
        }
        unordered_map<int, int> dist;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty())
        { // O((n+m) log n)
            auto [uWeight, uId] = pq.top();
            pq.pop();

            for (auto [v, vw] : adjList[uId])
            {
                if (!dist.count(v) || (dist.count(v) && uWeight + vw < dist[v]))
                {
                    dist[v] = uWeight + vw;
                    pq.emplace(dist[v], v);
                }
            }
        }
        for (int i = 0; i < q; i++)
        {
            int t;
            cin >> t;

            if (dist.count(t))
            {
                cout << dist[t] << "\n";
            }
            else
            {
                cout << "Impossible" << "\n";
            }
        }

        cout << "\n";
    }
}