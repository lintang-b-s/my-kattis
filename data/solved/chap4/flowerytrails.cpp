#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/flowerytrails?tab=metadata
int main()
{
    int P, T;
    cin >> P >> T;
    vector<vector<pair<int, int>>> adjList(P);

    for (int i = 0; i < T; i++)
    { // O(T), jumlah edges = T
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }


    unordered_map<int, int> dist;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty())
    {                                   // O((P+T) log P)
        auto [uWeight, uId] = pq.top(); //  O(log P)
        pq.pop();

        if (uWeight > dist[uId])
        {
            continue;
        }

        for (auto [v, vw] : adjList[uId])
        {
            if (!dist.count(v) || (dist.count(v) && uWeight + vw < dist[v]))
            {
                dist[v] = uWeight + vw;
                pq.emplace(dist[v], v); //  O(log P)
            }
        }
    }

    int tot = 0;
    queue<int> q;
    q.push(P - 1);
    unordered_set<int> visited;

    unordered_map<int, int> revDist;

    while (!q.empty())
    { // O(P+T)
        auto u = q.front();
        q.pop();
        if (visited.count(u))
        {
            continue;
        }

        visited.insert(u);

        for (auto [v, vw] : adjList[u])
        {
            if (dist[v] + vw == dist[u])
            {
                revDist[v] += vw;
                q.push(v);
            }
        }
    }
    for (auto [v, w] : revDist)
    {
        tot += w;
    }

    cout << tot * 2 << "\n";
}