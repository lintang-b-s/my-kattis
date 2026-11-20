#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (ll)1 << 61;

pair<ll, vector<int>>
bidirectional_dijkstra(vector<vector<pair<int, ll>>> outEdges,
                       vector<vector<pair<int, ll>>> inEdges,
                       int s, int t)
{
    int n = outEdges.size();
    vector<ll> distf(n), distb(n);
    vector<int> parf(n), parb(n);
    for (int v = 0; v < n; v++)
    {
        distf[v] = INF;
        distb[v] = INF;
        parf[v] = -1;
        parb[v] = -1;
    }
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pqf, pqb;
    vector<bool> scannedf(n), scannedb(n);
    int mid = -1;
    distf[s] = 0;
    distb[t] = 0;
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

    return {mu, sppath};
}

ll dijkstra(vector<vector<pair<int, ll>>> adjList, int s, int t)
{
    int n = adjList.size();
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
            return uDist;
        }

        for (auto [v, w] : adjList[u])
        {
            if (uDist + w < dist[v])
            {
                dist[v] = uDist + w;
                pq.push({dist[v], v});
            }
        }
    }

    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> outEdges(n + 1), inEdges(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        outEdges[u].push_back({v, w});
        outEdges[v].push_back({u, w});

        inEdges[v].push_back({u, w});
        inEdges[u].push_back({v, w});
    }

    auto [cost12, sppath12] = bidirectional_dijkstra(outEdges, inEdges, 1, 2);

    auto setengah = [&](ll u)
    {
        if (u % 2 != 0)
        {
            return u / 2 + 1;
        }
        return u / 2;
    };

    for (int i = 0; i < sppath12.size() - 1; i++)
    {
        int u = sppath12[i];
        int v = sppath12[i + 1];

        for (int j = 0; j < outEdges[u].size(); j++)
        {
            if (outEdges[u][j].first == v)
            {
                outEdges[u][j].second = setengah(outEdges[u][j].second);
            }
        }

        for (int j = 0; j < outEdges[v].size(); j++)
        {
            if (outEdges[v][j].first == u)
            {
                outEdges[v][j].second = setengah(outEdges[v][j].second);
            }
        }

        for (int j = 0; j < inEdges[u].size(); j++)
        {
            if (inEdges[u][j].first == v)
            {
                inEdges[u][j].second = setengah(inEdges[u][j].second);
            }
        }

        for (int j = 0; j < inEdges[v].size(); j++)
        {
            if (inEdges[v][j].first == u)
            {
                inEdges[v][j].second = setengah(inEdges[v][j].second);
            }
        }
    }

    auto [cost23, sppath23] = bidirectional_dijkstra(outEdges, inEdges, 2, 3);
    cout << cost12 + cost23 << endl;
}
