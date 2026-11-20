
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
// https://codeforces.com/contest/1938/submit

const ll INF = ((ll)1 << 62) - 1;

struct BDResult
{
    vector<ll> distf, distb;
    vector<bool> scannedf, scannedb;
    vector<int> sppath;
    ll mu;
};

BDResult bidirectionalDijkstra(vector<std::vector<std::pair<int, ll>>> outEdges,
                               vector<std::vector<std::pair<int, ll>>> inEdges,
                               int s, int t)
{
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pqf, pqb;
    int n = outEdges.size();
    vector<ll> distf(n), distb(n);
    vector<bool> scannedf(n), scannedb(n);
    vector<int> parf(n), parb(n);
    for (int v = 0; v < n; v++)
    {
        distf[v] = INF;
        distb[v] = INF;
        parf[v] = -1;
        parb[v] = -1;
    }

    distf[s] = 0;
    distb[t] = 0;
    int mid = -1;

    pqf.push({0, s});
    pqb.push({0, t});

    ll mu = 2 * INF;

    while (!pqf.empty() && !pqb.empty())
    {
        auto [usDist, us] = pqf.top();
        auto [utDist, ut] = pqb.top();
        pqf.pop();
        pqb.pop();

        bool bothOk = usDist == distf[us] && utDist == distb[ut];
        if (bothOk && usDist + utDist >= mu)
        {
            break;
        }

        if (usDist == distf[us])
        {
            scannedf[us] = true;
            for (auto [v, w] : outEdges[us])
            {
                if (usDist + w < distf[v])
                {
                    parf[v] = us;
                    distf[v] = usDist + w;
                    pqf.push({distf[v], v});
                }

                ll newDist = distf[v] + distb[v];
                if (scannedb[v] && newDist < mu)
                {
                    mu = newDist;
                    mid = v;
                }
            }
        }

        if (utDist == distb[ut])
        {
            scannedb[ut] = true;
            for (auto [v, w] : inEdges[ut])
            {
                if (utDist + w < distb[v])
                {
                    parb[v] = ut;
                    distb[v] = utDist + w;
                    pqb.push({distb[v], v});
                }

                ll newDist = distf[v] + distb[v];
                if (scannedf[v] && newDist < mu)
                {
                    mu = newDist;
                    mid = v;
                }
            }
        }
    }

    vector<int> sppath;
    int u = mid;

    while (u != -1)
    {
        sppath.push_back(u);
        u = parf[u];
    }

    reverse(sppath.begin(), sppath.end());

    u = mid;
    while (u != -1)
    {
        if (u != mid)
        {
            sppath.push_back(u);
        }
        u = parb[u];
    }

    return {distf, distb, scannedf, scannedb, sppath, mu};
}

vector<ll> dijkstra(vector<vector<pair<int, ll>>> outEdges, int s, int t)
{
    int n = outEdges.size();
    vector<ll> dist(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    for (int v = 0; v < n; v++)
    {
        dist[v] = INF;
    }

    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty())
    {
        auto [uDist, u] = pq.top();
        pq.pop();

        if (uDist != dist[u])
        {
            continue;
        }

        if (u == t)
        {
            break;
        }

        for (auto [v, w] : outEdges[u])
        {
            if (uDist + w < dist[v])
            {
                dist[v] = uDist + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> outEdges(n + 1);
    vector<vector<pair<int, ll>>> edges(n + 1);

    vector<vector<pair<int, ll>>> inEdges(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        outEdges[u].push_back({v, t});
        edges[u].push_back({v, t});
        outEdges[v]
            .push_back({u, t});

        inEdges[v].push_back({u, t});
        inEdges[u].push_back({v, t});
    }

    auto bdr = bidirectionalDijkstra(outEdges, inEdges, 1, n);
    auto distf = dijkstra(outEdges, 1, n);
    auto distb = dijkstra(outEdges, n, 1);
    auto sppath = bdr.sppath;
    auto mu = bdr.mu;

    auto getKey = [](int u, int v)
    {
        return ((ll)u << 32) | (ll)(v);
    };

    unordered_set<ll> sppathset;
    for (int i = 1; i < sppath.size(); i++)
    {
        int u = sppath[i - 1];
        int v = sppath[i];
        ll key = getKey(u, v);
        sppathset.insert(key);
    }

    ll spDist = mu;

    ll minTravelTime = INF;
    for (int u = 1; u < n + 1; u++)
    {
        for (auto e : edges[u])
        {
            int v = e.first;

            ll key = getKey(u, v);
            ll keyRev = getKey(v, u);

            bool eNotInSp = sppathset.find(key) == sppathset.end() && sppathset.find(key) == sppathset.end();
            bool eRevNotInSp = sppathset.find(keyRev) == sppathset.end() && sppathset.find(key) == sppathset.end();

            if (eNotInSp && eRevNotInSp)
            {
                minTravelTime = min(minTravelTime, distf[u] + distb[v] + e.second);
                minTravelTime = min(minTravelTime, distb[u] + distf[v] + e.second);
            }
        }
    }

    if (minTravelTime == INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << minTravelTime + mu << endl;
    }
}