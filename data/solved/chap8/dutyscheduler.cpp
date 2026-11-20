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
    int m, n;
    cin >> m >> n;
    unordered_map<string, int> raIds;
    unordered_map<string, vector<int>> raDays;

    int vId = n + 1;
    for (int i = 0; i < m; i++)
    {
        string raName;
        int d;
        cin >> raName >> d;
        raIds[raName] = vId;
        vId++;

        for (int j = 0; j < d; j++)
        {
            int day;
            cin >> day;
            raDays[raName].push_back(day);
        }
    }

    int s = n + m + 1;
    int t = n + m + 2;

    auto runDinic = [&](int k, maxFlow &dinic) -> bool
    {
        for (auto [raName, curId] : raIds)
        {
            dinic.add_edge(s, curId, k);
        }

        for (auto [raName, days] : raDays)
        {
            int curId = raIds[raName];
            for (auto day : days)
            {
                dinic.add_edge(curId, day, 1);
            }
        }

        for (int d = 1; d <= n; d++)
        {
            dinic.add_edge(d, t, 2);
        }

        ll mf = dinic.findMaxFlow(s, t);
        if (mf == 2 * n)
        {
            return true;
        }

        return false;
    };

    for (int k = 1; k <= n; k++)
    { // O(n * (n+m+3)^2 * (m+mn+n))
        maxFlow dinic(n + m + 3);

        bool validAssignment = runDinic(k, dinic); // O((n+m+3)^2 * (m+mn+n))
        if (validAssignment)
        {
            cout << k << "\n";
            auto mfEdges = dinic.getEdges();
            auto adjList = dinic.getAdjacencyList();

            vector<vector<string>> assignments(n + 1);

            for (auto [raName, id] : raIds)
            { // O(mn)

                for (auto &idx : adjList[id])
                { // worst case O(n)
                    auto &[day, cap, flow] = mfEdges[idx];
                    if (day <= n && flow == 1)
                    {
                        assignments[day].push_back(raName);
                    }
                }
            }

            for (int day = 1; day <= n; day++)
            {
                cout << "Day " << day << ":";
                for (auto raName : assignments[day])
                {
                    cout << " " << raName;
                }
                cout << "\n";
            }

            break;
        }
    }
}