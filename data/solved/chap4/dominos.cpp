#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

enum
{
    UNVISITED = -1
};
typedef long long ll;

void Kosaraju(int u, int pass, vi &dfs_num, vector<vii> &AL, vector<vii> &AL_T,
              vi &S, vi &scc)
{ // O(V+E)
    dfs_num[u] = 1;
    auto &neighbor = (pass == 1) ? AL[u] : AL_T[u];
    for (auto &[v, w] : neighbor)
    {
        if (dfs_num[v] == UNVISITED)
        {
            Kosaraju(v, pass, dfs_num, AL, AL_T, S, scc);
        }
    }
    S.push_back(u);
    scc.push_back(u);
}

void tarjanSCC(int u, vi &dfs_num, vector<vii> &AL, vi &dfs_low, int &dfsNumberCounter,
               stack<int> &St, vi &visited, int &numSCC, vector<int> &roots, vi &sccIds)
{ // O(V+E)
    dfs_low[u] = dfs_num[u] = dfsNumberCounter;
    dfsNumberCounter++;
    St.push(u);
    visited[u] = 1;
    for (auto &[v, w] : AL[u])
    {
        if (dfs_num[v] == UNVISITED)
        {
            tarjanSCC(v, dfs_num, AL, dfs_low, dfsNumberCounter, St, visited, numSCC, roots,
                      sccIds);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }

        if (visited[v])
        {
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
    }
    if (dfs_low[u] == dfs_num[u])
    {
        sccIds[u] = numSCC;
        ++numSCC;
        while (true)
        {
            int v = St.top();
            St.pop();
            visited[v] = 0;
            roots[v] = u;
            if (u == v)
            {
                break;
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        int dfsNumberCounter, numSCC;
        vector<vii> AL(n), AL_T(n);
        vi S, visited;
        stack<int> St;

        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            AL[x - 1].push_back({y - 1, 1});
            AL_T[y - 1].push_back({x - 1, 1});
        }

        vi dfs_num(n, UNVISITED);
        for (int u = 0; u < n; u++)
        { // O(V+E)
            if (dfs_num[u] == UNVISITED)
            {
                vi scc;
                Kosaraju(u, 1, dfs_num, AL, AL_T, S, scc);
            }
        }

        numSCC = 0;
        dfs_num.assign(n, UNVISITED);

        vector<int> roots(n, 0);

        vector<vi> sccs;
        vector<int> sccIds(n);
        for (int i = n - 1; i >= 0; i--)
        { // O(V+E)
            if (dfs_num[S[i]] == UNVISITED)
            {
                vi scc;
                ++numSCC, Kosaraju(S[i], 2, dfs_num, AL, AL_T, S, scc);
                sccs.push_back(scc);
                int root;
                if (scc.size() > 0)
                {
                    root = scc[0];
                }
                for (auto u : scc)
                {
                    roots[u] = root;
                }
                sccIds[root] = numSCC - 1;
            }
        }

        vector<int> inDegCondensation(numSCC, 0);

        for (int u = 0; u < n; u++)
        { // O(V+E)
            for (auto v : AL[u])
            {
                if (roots[v.first] != roots[u])
                {
                    inDegCondensation[sccIds[roots[v.first]]]++;
                }
            }
        }

        int knock = 0;
        for (auto indeg : inDegCondensation)
        { 
            if (indeg == 0)
            {
                knock++;
            }
        }
        cout << knock << "\n";
    }
}