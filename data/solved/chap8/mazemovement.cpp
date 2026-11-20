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
    int n;
    cin >> n;
    vector<ll> rooms(n);

    for (int i = 0; i < n; i++)
    {
        cin >> rooms[i];
    }

    sort(rooms.begin(), rooms.end()); // O(n*logn)

    maxFlow dinic(n);
    int source = 0;
    int target = n - 1;

    for (int i = 0; i < n; i++)
    {
        int u = rooms[i];
        for (int j = i + 1; j < n; j++)
        {
            int v = rooms[j];
            int fpb = gcd(u, v);
            if (gcd(u, v) > 1)
            {
                dinic.add_edge(i, j, fpb);
                dinic.add_edge(j, i, fpb);
            }
        }
    }

    ll mf = dinic.findMaxFlow(source, target); // O(n^2 *E), E=jumlah edges
    cout << mf << "\n";
}