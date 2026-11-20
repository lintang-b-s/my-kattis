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
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> childLikeToys(n);

    vector<vector<int>> categoryToys(p);
    vector<int> categoryMaxUsed(p);

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int toy;
            cin >> toy;
            childLikeToys[i].push_back(toy);
        }
    }

    for (int i = 0; i < p; i++)
    {
        int l, r;
        cin >> l;
        for (int j = 0; j < l; j++)
        {

            int toyj;
            cin >> toyj;
            categoryToys[i].push_back(toyj);
        }
        cin >> r;
        categoryMaxUsed[i] = r;
    }

    // vertices id:
    // source=0, target1
    // childrens c_1, c_2, ..., c_n = 2,3,....,2+n-1
    // toys t_1,t_2,...,t_m = 2+n, 2+n+1, ..., 2+n+m-1
    // toy categories p_1, ... ,p_p = 2+n+m,... ,2+n+m+p-1
    maxFlow dinic(2 + n + m + p);

    int source = 0;
    int target = 1;
    for (int i = 1; i <= n; i++)
    {
        // source ke anak
        dinic.add_edge(source, i + 1, 1);

        // anak ke toy
        for (auto toy : childLikeToys[i - 1])
        {
            dinic.add_edge(i + 1, (n + 1) + toy, 1);
        }
    }

    unordered_set<int> toysWithCategory;

    for (int i = 1; i <= categoryToys.size(); i++)
    {
        auto toys = categoryToys[i - 1];
        for (auto toy : toys)
        {
            dinic.add_edge((n + 1) + toy, (n + m + 1) + i, 1);
            toysWithCategory.insert(toy);
        }

        // categories ke target
        dinic.add_edge((n + m + 1) + i, target, categoryMaxUsed[i - 1]);
    }

    for (int toy = 1; toy <= m; toy++)
    {
        if (!toysWithCategory.count(toy))
        {
            dinic.add_edge((n + 1) + toy, target, 1);
        }
    }

    ll mf = dinic.findMaxFlow(source, target);
    cout << mf << "\n";
}