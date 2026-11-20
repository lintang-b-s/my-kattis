#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = (ll)1 << 61;

class maxFlow
{
private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool bfs(int s, int t)
    {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == t)
            {
                break;
            }
            for (auto &idx : AL[u])
            {
                auto &[v, cap, flow] = EL[idx];
                if ((cap - flow) > 0 && (d[v] == -1))
                {
                    d[v] = d[u] + 1;
                    q.push(v);
                    p[v] = {u, idx};
                }
            }
        }
        return d[t] != -1;
    }

    ll dfs(int u, int t, ll f = INF)
    {
        if ((u == t) || (f == 0))
        {
            return f;
        }
        for (int &i = last[u]; i < (int)AL[u].size(); i++)
        {
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1)
            {
                continue;
            }
            if (ll pushed = dfs(v, t, min(f, cap - flow)))
            {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    maxFlow(int initialV) : V(initialV)
    {
        EL.clear();
        AL.assign(V, vi());
    }

    void add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v)
        {
            return;
        }
        EL.emplace_back(v, w, 0);
        AL[u].push_back(EL.size() - 1);
        EL.emplace_back(u, directed ? 0 : w, 0);
        AL[v].push_back(EL.size() - 1);
    }

    ll findMaxFlow(int s, int t)
    { // O(V^2 * E)
        ll mf = 0;
        while (bfs(s, t))
        {
            last.assign(V, 0);
            while (ll f = dfs(s, t))
            {
                mf += f;
            }
        }
        return mf;
    }

    vector<edge> getEdges()
    {
        return EL;
    }

    vector<vi> getAdjacencyList()
    {
        return AL;
    }
};

struct BDResult
{
    vector<ll> distf, distb;
    vector<bool> scannedf, scannedb;
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
    for (int v = 0; v < n; v++)
    {
        distf[v] = INF;
        distb[v] = INF;
    }

    distf[s] = 0;
    distb[t] = 0;

    pqf.push({0, s});
    pqb.push({0, t});

    ll mu = 2 * INF;

    while (pqf.size() > 0 && pqb.size() > 0)
    {
        auto [usDist, us] = pqf.top();
        auto [utDist, ut] = pqb.top();
        pqf.pop();
        pqb.pop();

        // bool bothTrue = (usDist == distf[us]) && (utDist == distb[ut]);

        // if (bothTrue && usDist + utDist >= mu)
        // {
        //     break;
        // }

        if (usDist == distf[us])
        {
            scannedf[us] = true;

            for (auto [v, t] : outEdges[us])
            {
                ll newDist = usDist + t;
                if (newDist < distf[v])
                {
                    distf[v] = newDist;
                    pair<ll, int> newPair = {
                        newDist,
                        v,
                    };
                    pqf.push(newPair);
                }

                bool vScannedBackward = scannedb[v];
                if (vScannedBackward)
                {
                    ll newstDist = newDist + distb[v];
                    if (newstDist <= mu)
                    {
                        mu = newstDist;
                    }
                }
            }
        }

        if (utDist == distb[ut])
        {
            scannedb[ut] = true;

            for (auto [v, t] : inEdges[ut])
            {
                ll newDist = utDist + t;
                if (newDist < distb[v])
                {
                    distb[v] = newDist;
                    pair<ll, int> newPair = {
                        newDist,
                        v,
                    };
                    pqb.push(newPair);
                }

                bool vScannedForward = scannedf[v];
                if (vScannedForward)
                {
                    ll newstDist = newDist + distf[v];
                    if (newstDist <= mu)
                    {
                        mu = newstDist;
                    }
                }
            }
        }
    }

    return {distf, distb, scannedf, scannedb, mu};
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> outEdges(n + 1);
    vector<vector<pair<int, ll>>> inEdges(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        outEdges[u].push_back({v, t});
        outEdges[v].push_back({u, t});

        inEdges[v].push_back({u, t});
        inEdges[u].push_back({v, t});
    }

    auto [distf, distb, scannedf, scannedb, mu] = bidirectionalDijkstra(outEdges, inEdges, 1, n);

    ll spDist = mu;

    maxFlow dinic(n + 1);

    for (int u = 1; u < n + 1; u++)
    {
        for (auto e : outEdges[u])
        {
            int v = e.first;

            bool eInSp = distf[u] + distb[v] + e.second == spDist;

            if (eInSp)
            {
                dinic.add_edge(u, v, 1, true);
            }
        }
    }

    cout << dinic.findMaxFlow(1, n) << endl;
}