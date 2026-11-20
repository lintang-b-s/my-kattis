#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;
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

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adjList(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
    }

    auto dijkstra = [&](int s)
    {
        unordered_map<int, ll> dist;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty())
        {
            auto [uDist, u] = pq.top();
            pq.pop();

            if (dist.count(u) && uDist > dist[u])
            {
                continue;
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

    // karna n<=100, dist[u][v] simpan key hashmap: u | (v << 16)
    auto bitpack = [&](int u, int v)
    {
        return u | (v << 16);
    };

    unordered_map<ll, ll> dist; // all pairs shortest path

    for (int s = 1; s <= n; s++)
    { // O(n * (m+n)logn)

        auto sdist = dijkstra(s); // O((m+n)logn)
        for (int t = 1; t <= n; t++)
        { // O(n)
            auto pp = bitpack(s, t);
            dist[pp] = sdist[t];
        }
    }

    vector<tuple<int, int, int>> tripRequest;
    for (int i = 0; i < k; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        tripRequest.push_back({u, v, t});
    }

    int source = 0;
    int sink = 1;

    maxFlow dinic(k * 2 + 2);

    for (int i = 1; i <= tripRequest.size(); i++)
    {
        auto [u, v, ut] = tripRequest[i - 1];
        dinic.add_edge(source, i + 1, 1);
        dinic.add_edge(i + k + 1, sink, 1);
        for (int j = 1; j <= tripRequest.size(); j++)
        {
            auto [q, w, qt] = tripRequest[j - 1];
            if (i == j)
            {
                continue;
            }
            if (ut + dist[bitpack(u, v)] + dist[bitpack(v, q)] <= qt)
            {
                dinic.add_edge(i + 1, j + k + 1, 1);
            }
        }
    }

    ll mf = dinic.findMaxFlow(source, sink); // O(k^2 * E)
    cout << k - mf << "\n";
}
