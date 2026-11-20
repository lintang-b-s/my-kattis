#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int id;
    int v;
    int w;
    unordered_set<int> from_server_blacklists;
};

const int INF = 1 << 28;

struct BDResult
{
    vector<int> distf, distb;
    vector<bool> scannedf, scannedb;
    int mu;
};

BDResult bidirectional_dijkstra(vector<std::vector<std::pair<int, int>>> outEdges,
                                vector<std::vector<std::pair<int, int>>> inEdges,
                                int s, int t)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pqf, pqb;
    int n = outEdges.size();
    vector<int> distf(n), distb(n);
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

    int mu = 2 * INF;

    while (pqf.size() > 0 && pqb.size() > 0)
    {
        auto [usDist, us] = pqf.top();
        auto [utDist, ut] = pqb.top();
        pqf.pop();
        pqb.pop();

        bool bothTrue = (usDist == distf[us]) && (utDist == distb[ut]);

        if (bothTrue && usDist + utDist >= mu)
        {
            break;
        }

        if (usDist == distf[us])
        {
            scannedf[us] = true;

            for (auto [v, w] : outEdges[us])
            {
                int newDist = usDist + w;
                if (newDist < distf[v])
                {
                    distf[v] = newDist;
                    pair<int, int> newPair = {
                        newDist,
                        v,
                    };
                    pqf.push(newPair);
                }

                bool vScannedBackward = scannedb[v];
                if (vScannedBackward)
                {
                    int newstDist = newDist + distb[v];
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

            for (auto [v, w] : inEdges[ut])
            {
                int newDist = utDist + w;
                if (newDist < distb[v])
                {
                    distb[v] = newDist;
                    pair<int, int> newPair = {
                        newDist,
                        v,
                    };
                    pqb.push(newPair);
                }

                bool vScannedForward = scannedf[v];
                if (vScannedForward)
                {
                    int newstDist = newDist + distf[v];
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
    int n;
    cin >> n;

    vector<vector<edge>> adjList(n);

    int vnProcessTime = 0;
    int eId = 0;
    for (int i = 0; i < n; i++)
    {
        int m, t;
        cin >> m >> t;
        for (int j = 0; j < m; j++)
        {
            int s, x;
            cin >> s >> x;
            unordered_set<int> froms;
            for (int k = 0; k < s; k++)
            {
                int a;
                cin >> a;
                a--;
                froms.insert(a);
            }
            x--;
            adjList[i].push_back({eId, x, t, froms});
            eId++;
        }
        if (i == n - 1)
        {
            vnProcessTime = t;
        }
    }

    // ubah ke arc-expanded graph
    vector<vector<pair<int, int>>> arcExpOutEdges(eId + 2);
    vector<vector<pair<int, int>>> arcExpInEdges(eId + 2);

    int source = eId;
    int target = eId + 1;

    for (int u = 0; u < n; u++)
    {
        for (auto e : adjList[u])
        {
            for (auto e2 : adjList[e.v])
            {
                if (e2.from_server_blacklists.find(u) != e2.from_server_blacklists.end())
                {
                    continue;
                }

                arcExpOutEdges[e.id].push_back({e2.id, e.w});
                arcExpInEdges[e2.id].push_back({e.id, e.w});
            }

            if (u == 0)
            {
                // artificial source edge
                arcExpOutEdges[source].push_back({e.id, 0});
                arcExpInEdges[e.id].push_back({source, 0});
            }

            if (e.v == n - 1)
            {
                // artificial target edge
                arcExpOutEdges[e.id].push_back({target, e.w});
                arcExpInEdges[target].push_back({e.id, e.w});
            }
        }
    }

    auto bdr = bidirectional_dijkstra(arcExpOutEdges, arcExpInEdges, source, target);
    auto mu = bdr.mu + vnProcessTime;
    if (mu < INF)
    {
        cout << mu << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
}
