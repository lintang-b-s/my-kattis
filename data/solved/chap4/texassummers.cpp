#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// https://open.kattis.com/problems/texassummers?tab=metadata

int main()
{
    int n;
    cin >> n;

    vector<pair<ll, ll>> coords;

    int shadyN = n;
    for (int i = 0; i < n; i++)
    {
        ll u, v;
        cin >> u >> v;
        coords.push_back({u, v});
    }

    ll sx, sy, tx, ty;
    cin >> sx >> sy;
    cin >> tx >> ty;
    coords.push_back({sx, sy});
    coords.push_back({tx, ty});

    n = coords.size();
    vector<vector<pair<int, ll>>> adjList(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            ll xdiff = (coords[i].first - coords[j].first);
            ll ydiff = (coords[i].second - coords[j].second);
            ll dist = xdiff * xdiff + ydiff * ydiff;
            adjList[i].push_back({j, dist});
        }
    }

    unordered_map<int, ll> dist;
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<pair<int, ll>>> pq;

    int sid = find(coords.begin(), coords.end(), make_pair(sx, sy)) - coords.begin();

    int tid = find(coords.begin(), coords.end(), make_pair(tx, ty)) - coords.begin();

    unordered_map<int, int> parent;
    dist[sid] = 0;
    pq.emplace(0, sid);
    while (!pq.empty())
    { // O((n+m) log n), m = n(n-1)/2 karena complete graph
        auto [uDist, u] = pq.top();
        pq.pop();
        if (uDist > dist[u])
        {
            continue;
        }
        for (auto [v, vw] : adjList[u])
        {
            if (!dist.count(v) || (dist.count(v) && dist[u] + vw < dist[v]))
            {
                dist[v] = dist[u] + vw;
                pq.emplace(dist[v], v);
                parent[v] = u;
            }
        }
    }

    int end = tid;
    vector<int> shadyPath;
    while (parent.find(end) != parent.end())
    {
        if (end < shadyN)
        {
            shadyPath.push_back(end);
        }
        end = parent[end];
    }
    reverse(shadyPath.begin(), shadyPath.end());

    for (auto p : shadyPath)
    {
        cout << p << "\n";
    }
    if (shadyPath.size() == 0)
    {
        cout << "-" << "\n";
    }
}