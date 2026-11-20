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
    int N, K, M;
    cin >> N >> K >> M;

    vector<vector<pair<int, int>>> edges;
    int source = 0;
    int sink = 1;
    maxFlow dinic(N * K + 2);
    int vId = 2;

    auto bitpack = [](int i, int j) -> ll
    {
        return i | (j << 16);
    };

    unordered_map<ll, int> junctionToVId;
    for (int i = vId; i <= N + 1; i++)
    { 
        for (int t = 0; t < K; t++)
        {
            junctionToVId[bitpack(i, t)] = vId;
            vId++;
        }
    }
    for (int i = 2; i <= K + 1; i++)
    {
        dinic.add_edge(source, junctionToVId[bitpack(i, i - 2)], 1);
    }

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;

        for (int t = 0; t < K; t++)
        {
            dinic.add_edge(junctionToVId[bitpack(u + 1, t)], junctionToVId[bitpack(v + 1, (t + 1) % K)], 1);
        }
    }

    for (int t = 0; t < K; t++)
    {
        dinic.add_edge(junctionToVId[bitpack(( N + 1), t)], sink, INF);
    }

    ll mf = dinic.findMaxFlow(source, sink);
    cout << mf << "\n";
}