#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF_WEIGHT = (ll)1 << 62;

int main()
{
    int n, m;
    cin >> n >> m;

    struct edge
    {
        int from, to;
        int weight;
    };
    vector<vector<pair<int, ll>>> adjList(n);
    vector<edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        int a, b, d;
        cin >> a >> b >> d;
        adjList[a].push_back({b, d});
        adjList[b].push_back({a, d});
        edges[i] = edge{a, b, d};
    }

    int delft = 0;
    int amsterdam = 1;

    unordered_map<int, ll> dist;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    unordered_map<int, int> parent;

    parent[amsterdam] = -1;

    dist[amsterdam] = 0;

    pq.emplace(0, amsterdam);

    while (!pq.empty())
    { // O((n+m)log n)
        auto [uDist, u] = pq.top();
        pq.pop();

        for (auto [v, vDist] : adjList[u])
        {
            if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
            {
                dist[v] = uDist + vDist;
                pq.emplace(dist[v], v);
                parent[v] = u;
            }
        }
    }

    unordered_set<ll> edgesTerlarang;

    for (int v = 0; v < n; v++)
    {
        if (v == amsterdam) {
            continue;
        }
        vector<int> path(0);
        int cur = v;
        path.push_back(cur);
        while (parent[cur] != -1)
        {
            path.push_back(parent[cur]);
            cur = parent[cur];
        }

        reverse(path.begin(), path.end());

        cout << "tes";
    }

    // 2<=n<=10^5
    // bisa bitpacking 20 bit awal and next 20 bit
    auto bitpack = [](int u, int v)
    {
        return u | (v << 20);
    };

    auto unpack = [](ll e)
    {
        return make_pair(e, e >> 20); // (u,v)
    };

    for (auto e : edges)
    {
        if (dist[e.from] + e.weight == dist[e.to])
        {

            edgesTerlarang.insert(bitpack(e.to, e.from));
        }

        if (dist[e.to] + e.weight == dist[e.from])
        {
            edgesTerlarang.insert(bitpack(e.from, e.to));
        }
    }

    // TLE
    // for (int v = 0; v < n; v++)
    // { // worst case O(n^2)
    //     int cur = v;

    //     while (parent[cur] != -1)
    //     { // worst case O(n)
    //         auto u = parent[cur];
    //         edgesTerlarang.insert(bitpack(cur, u));
    //         cur = parent[cur];
    //     }
    // }

    vector<vector<pair<int, ll>>> adjList2(n);

    for (int u = 0; u < adjList.size(); u++)
    { // O(n+m)
        for (int j = 0; j < adjList[u].size(); j++)
        {
            auto [v, vDist] = adjList[u][j];
            if (!edgesTerlarang.count(bitpack(u, v)))
            {
                adjList2[u].push_back({v, vDist});
            }
        }
    }

    queue<int> qq;
    vector<bool> visited(n, false);
    unordered_map<int, int> parent2;
    parent2[delft] = -1;
    visited[delft] = true;
    qq.push(delft);

    while (!qq.empty())
    { // O(n+m)
        auto u = qq.front();
        qq.pop();

        for (auto [v, vDist] : adjList2[u])
        {
            if (!visited[v])
            {
                qq.push(v);
                visited[v] = true;
                parent2[v] = u;
            }
        }
    }

    if (!visited[amsterdam])
    {
        cout << "impossible" << "\n";
    }
    else
    {
        vector<int> path(0);
        path.push_back(amsterdam);
        int cur = amsterdam;

        while (parent2[cur] != -1)
        { // O(n)
            path.push_back(parent2[cur]);
            cur = parent2[cur];
        }
        reverse(path.begin(), path.end());
        cout << path.size();

        for (auto p : path)
        {
            cout << " " << p;
        }
    }
}

// TLE
// int main()
// {
//     int n, m;
//     cin >> n >> m;

//     vector<vector<pair<int, ll>>> adjList(n);
//     for (int i = 0; i < m; i++)
//     {
//         int a, b, d;
//         cin >> a >> b >> d;
//         adjList[a].push_back({b, d});
//         adjList[b].push_back({a, d});
//     }

//     int delft = 0;
//     int amsterdam = 1;

//     unordered_map<int, ll> dist;
//     priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

//     unordered_map<int, int> parent;

//     parent[amsterdam] = -1;

//     dist[amsterdam] = 0;

//     pq.emplace(0, amsterdam);

//     while (!pq.empty())
//     { // O((n+m)log n)
//         auto [uDist, u] = pq.top();
//         pq.pop();

//         if (uDist > dist[u])
//         {
//             continue;
//         }

//         for (auto [v, vDist] : adjList[u])
//         {
//             if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
//             {
//                 dist[v] = uDist + vDist;
//                 pq.emplace(dist[v], v);
//                 parent[v] = u;
//             }
//         }
//     }

//     unordered_set<ll> edgesTerlarang;

//     // 2<=n<=10^5
//     // bisa bitpacking 20 bit awal and next 20 bit
//     auto bitpack = [](int u, int v)
//     {
//         return u | (v << 20);
//     };

//     auto unpack = [](ll e)
//     {
//         return make_pair(e, e >> 20); // (u,v)
//     };

//     for (int v = 0; v < n; v++)
//     { // worst case O(n^2)
//         int cur = v;

//         while (parent[cur] != -1)
//         { // worst case O(n)
//             auto u = parent[cur];
//             edgesTerlarang.insert(bitpack(cur, u));
//             cur = parent[cur];
//         }
//     }

//     vector<vector<pair<int, ll>>> adjList2(n);

//     for (int u = 0; u < adjList.size(); u++)
//     { // O(n+m)
//         for (int j = 0; j < adjList[u].size(); j++)
//         {
//             auto [v, vDist] = adjList[u][j];
//             if (!edgesTerlarang.count(bitpack(u, v)))
//             {
//                 adjList2[u].push_back({v, vDist});
//             }
//         }
//     }

//     unordered_map<int, ll> dist2;
//     priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq2;

//     unordered_map<int, int> parent2;

//     parent2[delft] = -1;

//     dist2[delft] = 0;

//     pq2.emplace(0, delft);

//     while (!pq2.empty())
//     { // O((n+m)log n)
//         auto [uDist, u] = pq2.top();
//         pq2.pop();

//         if (uDist > dist2[u])
//         {
//             continue;
//         }

//         for (auto [v, vDist] : adjList2[u])
//         {
//             if (!dist2.count(v) || (dist2.count(v) && uDist + vDist < dist2[v]))
//             {
//                 dist2[v] = uDist + vDist;
//                 pq2.emplace(dist2[v], v);
//                 parent2[v] = u;
//             }
//         }
//     }

//     if (!dist2.count(amsterdam) || (dist2.count(amsterdam) && dist2[amsterdam] == INF_WEIGHT))
//     {
//         cout << "impossible" << "\n";
//     }
//     else
//     {
//         vector<int> path(0);
//         path.push_back(amsterdam);
//         int cur = amsterdam;

//         while (parent2[cur] != -1)
//         { // O(n)
//             path.push_back(parent2[cur]);
//             cur = parent2[cur];
//         }
//         reverse(path.begin(), path.end());
//         cout << path.size();

//         for (auto p : path)
//         {
//             cout << " " << p;
//         }
//     }
// }

// WA
// int main()
// {
//     int n, m;
//     cin >> n >> m;

//     vector<vector<pair<int, ll>>> adjList(n);
//     for (int i = 0; i < m; i++)
//     {
//         int a, b, d;
//         cin >> a >> b >> d;
//         adjList[a].push_back({b, d});
//         adjList[b].push_back({a, d});
//     }

//     int delft = 0;
//     int amsterdam = 1;

//     unordered_map<int, ll> dist;
//     priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

//     unordered_map<int, int> parent;

//     parent[amsterdam] = -1;

//     dist[amsterdam] = 0;

//     pq.emplace(0, amsterdam);

//     while (!pq.empty())
//     { // O((n+m)log n)
//         auto [uDist, u] = pq.top();
//         pq.pop();

//         if (uDist > dist[u])
//         {
//             continue;
//         }

//         for (auto [v, vDist] : adjList[u])
//         {
//             if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
//             {
//                 dist[v] = uDist + vDist;
//                 pq.emplace(dist[v], v);
//                 parent[v] = u;
//             }
//         }
//     }

//     unordered_set<ll> edgesTerlarang;

//     // 2<=n<=10^5
//     // bisa bitpacking 20 bit awal and next 20 bit
//     auto bitpack = [](int u, int v)
//     {
//         return u | (v << 20);
//     };

//     auto unpack = [](ll e)
//     {
//         return make_pair(e, e >> 20); // (u,v)
//     };

// for (int v = 0; v < n; v++)
// { // worst case O(n^2)
//     int cur = v;

//     while (parent[cur] != -1)
//     { // worst case O(n)
//         auto u = parent[cur];
//         edgesTerlarang.insert(bitpack(cur, u));
//         cur = parent[cur];
//     }
// }

//     // buat bobot setiap edges terlarang jadi INF
//     for (int u = 0; u < adjList.size(); u++)
//     { // O(n+m)
//         for (int j = 0; j < adjList[u].size(); j++)
//         {
//             auto [v, vDist] = adjList[u][j];
//             if (edgesTerlarang.count(bitpack(u, v)))
//             {
//                 adjList[u][j] = make_pair(v, INF_WEIGHT);
//             }
//         }
//     }

//     unordered_map<int, ll> dist2;
//     priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq2;
//     unordered_map<int, int> parent2;

//     parent2[delft] = -1;

//     dist2[delft] = 0;

//     pq2.emplace(0, delft);

//     while (!pq2.empty())
//     { // O((n+m)log n)
//         auto [uDist, u] = pq2.top();
//         pq2.pop();

//         if (uDist > dist2[u])
//         {
//             continue;
//         }

//         for (auto [v, vDist] : adjList[u])
//         {
//             if (!dist2.count(v) || (dist2.count(v) && uDist + vDist < dist2[v]))
//             {
//                 dist2[v] = uDist + vDist;
//                 pq2.emplace(dist2[v], v);
//                 parent2[v] = u;
//             }
//         }
//     }

//     if (!dist2.count(amsterdam) || (dist2.count(amsterdam) && dist2[amsterdam] == INF_WEIGHT))
//     {
//         cout << "impossible" << "\n";
//     }
//     else
//     {
//         vector<int> path(0);
//         path.push_back(amsterdam);
//         int cur = amsterdam;

//         while (parent2[cur] != -1)
//         { // O(n)
//             path.push_back(parent2[cur]);
//             cur = parent2[cur];
//         }
//         reverse(path.begin(), path.end());
//         cout << path.size();

//         for (auto p : path)
//         {
//             cout << " " << p;
//         }
//     }
// }