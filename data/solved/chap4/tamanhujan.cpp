
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (ll)1 << 61;

vector<ll> dijkstra(vector<vector<pair<int, ll>>> adjList, int s)
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

        for (auto [v, w] : adjList[u])
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

struct midVertex
{
    int v;
    ll svdist, vtdist, stdist;
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> adjList(n + 1);           // bebas
    vector<vector<pair<int, ll>>> adjListTakBeratap(n + 1); // tak beratap
    vector<vector<pair<int, ll>>> adjListBeratap(n + 1);    // beratap

    vector<vector<pair<int, ll>>> outEdges(n + 1), inEdges(n + 1); // beratap

    for (int i = 0; i < m; i++)
    {
        int u, v, z;
        ll w;
        cin >> u >> v >> w >> z;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});

        if (z == 1)
        {
            // tak beratap
            adjListTakBeratap[u].push_back({v, w});
            adjListTakBeratap[v].push_back({u, w});
        }
        else
        {
            adjListBeratap[u].push_back({v, w});
            adjListBeratap[v].push_back({u, w});

            outEdges[u].push_back({v, w});
            outEdges[v].push_back({u, w});

            inEdges[v].push_back({u, w});
            inEdges[u].push_back({v, w});
        }
    }

    int s = 1, t = n;

    vector<ll> distBebas = dijkstra(adjList, s);
    vector<ll> distTakBeratap = dijkstra(adjListTakBeratap, s);

    vector<ll> distBeratapRev = dijkstra(adjListBeratap, t);

    int q;
    cin >> q;
    vector<ll> tt(q);
    vector<int> perm(q);
    for (int i = 0; i < q; i++)
    {
        cin >> tt[i];
        perm[i] = i;
    }

    sort(perm.begin(), perm.end(), [&](int a, int b)
         { return tt[a] < tt[b]; });

    vector<int> newToOld(q);

    vector<ll> sortedtt(q);
    for (int i = 0; i < q; i++)
    {
        sortedtt[i] = tt[perm[i]];
        newToOld[i] = perm[i];
    }
    vector<ll> res(q);

    vector<midVertex> midDist(n + 1);
    midDist[0] = midVertex{0, INF, INF, INF};

    for (int v = 1; v < n + 1; v++)
    {
        midDist[v] = midVertex{v, distBebas[v], distBeratapRev[v], distBebas[v] + distBeratapRev[v]};
    }

    sort(midDist.begin(), midDist.end(), [&](midVertex a, midVertex b)
         { return a.svdist < b.svdist; });

    auto upperBound = [&](ll target)
    {
        int l = 0, r = midDist.size() - 1;
        int ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (midDist[mid].svdist <= target)
            {
                l = mid + 1;
            }
            else
            {
                ans = mid;
                r = mid - 1;
            }
        }

        return ans;
    };

    vector<ll> prefMin(n + 1);

    prefMin[0] = midDist[0].stdist;
    for (int i = 1; i < n + 1; i++)
    {
        prefMin[i] = min(prefMin[i - 1], midDist[i].stdist);
    }

    for (int i = 0; i < q; i++)
    {
        ll time = sortedtt[i];
        if (distBebas[t] <= time)
        {
            res[newToOld[i]] = distBebas[t];
        }
        else
        {
            // ll minCost = INF;
            // for (int mid = 1; mid < n + 1; mid++)
            // {
            //     if (distBebas[mid] <= time)
            //     {
            //         minCost = min(minCost, midDist[mid]);
            //     }
            // }
            int ub = upperBound(time);
            if (ub == -1)
            {
                res[newToOld[i]] = -1;
            }
            else
            {
                int mid = ub - 1;
                res[newToOld[i]] = prefMin[mid];
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        if (res[i] >= INF)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << res[i] << endl;
        }
    }
}

// TLE 2
// int main()
// {
//     int n, m;
//     cin >> n >> m;
//     vector<vector<pair<int, ll>>> adjList(n + 1);           // bebas
//     vector<vector<pair<int, ll>>> adjListTakBeratap(n + 1); // tak beratap
//     vector<vector<pair<int, ll>>> adjListBeratap(n + 1);    // beratap

//     vector<vector<pair<int, ll>>> outEdges(n + 1), inEdges(n + 1); // beratap

//     for (int i = 0; i < m; i++)
//     {
//         int u, v, z;
//         ll w;
//         cin >> u >> v >> w >> z;
//         adjList[u].push_back({v, w});
//         adjList[v].push_back({u, w});

//         if (z == 1)
//         {
//             // tak beratap
//             adjListTakBeratap[u].push_back({v, w});
//             adjListTakBeratap[v].push_back({u, w});
//         }
//         else
//         {
//             adjListBeratap[u].push_back({v, w});
//             adjListBeratap[v].push_back({u, w});

//             outEdges[u].push_back({v, w});
//             outEdges[v].push_back({u, w});

//             inEdges[v].push_back({u, w});
//             inEdges[u].push_back({v, w});
//         }
//     }

//     int s = 1, t = n;

//     vector<ll> distBebas = dijkstra(adjList, s);
//     vector<ll> distTakBeratap = dijkstra(adjListTakBeratap, s);

//     vector<ll> distBeratapRev = dijkstra(adjListBeratap, t);

//     int q;
//     cin >> q;
//     vector<ll> tt(q);
//     vector<int> perm(q);
//     for (int i = 0; i < q; i++)
//     {
//         cin >> tt[i];
//         perm[i] = i;
//     }

//     sort(perm.begin(), perm.end(), [&](int a, int b)
//          { return tt[a] < tt[b]; });

//     vector<int> newToOld(q);

//     vector<ll> sortedtt(q);
//     for (int i = 0; i < q; i++)
//     {
//         sortedtt[i] = tt[perm[i]];
//         newToOld[i] = perm[i];
//     }
//     vector<ll> res(q);

//     vector<ll> midDist(n + 1);
//     for (int v = 1; v < n + 1; v++)
//     {
//         midDist[v] = distBebas[v] + distBeratapRev[v];
//     }

//     for (int i = 0; i < q; i++)
//     {
//         ll time = sortedtt[i];
//         if (distBebas[t] <= time)
//         {
//             res[newToOld[i]] = distBebas[t];
//         }
//         else
//         {
//             ll minCost = INF;
//             for (int mid = 1; mid < n + 1; mid++)
//             {
//                 if (distBebas[mid] <= time)
//                 {
//                     minCost = min(minCost, midDist[mid]);
//                 }
//             }

//             res[newToOld[i]] = minCost;
//         }
//     }

//     for (int i = 0; i < q; i++)
//     {
//         if (res[i] == INF)
//         {
//             cout << -1 << endl;
//         }
//         else
//         {
//             cout << res[i] << endl;
//         }
//     }
// }

// // https://kam.mff.cuni.cz/~spring/media/papers/5/bidirectional_dijkstra.pdf

// ll bidirectional_dijkstra(vector<vector<pair<int, ll>>> outEdges,
//                           vector<vector<pair<int, ll>>> inEdges,
//                           int s, int t)
// {
//     int n = outEdges.size();
//     vector<ll> distf(n), distb(n);

//     for (int v = 0; v < n; v++)
//     {
//         distf[v] = INF;
//         distb[v] = INF;
//     }
//     priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pqf, pqb;
//     vector<bool> scannedf(n), scannedb(n);
//     int mid = -1;
//     distf[s] = 0;
//     distb[t] = 0;
//     pqf.push({0, s});
//     pqb.push({0, t});
//     ll mu = 2 * INF;

//     while (!pqf.empty() && !pqb.empty())
//     {
//         auto [usDist, us] = pqf.top();
//         auto [utDist, ut] = pqb.top();
//         pqf.pop();
//         pqb.pop();

//         bool bothOk = usDist == distf[us] && utDist == distb[ut];
//         if (bothOk && usDist + utDist >= mu)
//         {
//             break;
//         }

//         if (usDist == distf[us])
//         {
//             scannedf[us] = true;
//             for (auto [v, w] : outEdges[us])
//             {
//                 if (usDist + w < distf[v])
//                 {

//                     distf[v] = usDist + w;
//                     pqf.push({distf[v], v});
//                 }

//                 ll newDist = distf[v] + distb[v];
//                 if (scannedb[v] && newDist < mu)
//                 {
//                     mu = newDist;
//                     mid = v;
//                 }
//             }
//         }

//         if (utDist == distb[ut])
//         {
//             scannedb[ut] = true;
//             for (auto [v, w] : inEdges[ut])
//             {
//                 if (utDist + w < distb[v])
//                 {

//                     distb[v] = utDist + w;
//                     pqb.push({distb[v], v});
//                 }

//                 ll newDist = distf[v] + distb[v];
//                 if (scannedf[v] && newDist < mu)
//                 {
//                     mu = newDist;
//                     mid = v;
//                 }
//             }
//         }
//     }

//     return mu;
// }

// TLE
// int main()
// {
//     int n, m;
//     cin >> n >> m;
//     vector<vector<pair<int, ll>>> adjList(n + 1);           // bebas
//     vector<vector<pair<int, ll>>> adjListTakBeratap(n + 1); // tak beratap

//     vector<vector<pair<int, ll>>> outEdges(n + 1), inEdges(n + 1); // beratap

//     for (int i = 0; i < m; i++)
//     {
//         int u, v, z;
//         ll w;
//         cin >> u >> v >> w >> z;
//         adjList[u].push_back({v, w});
//         adjList[v].push_back({u, w});

//         if (z == 1)
//         {
//             // tak beratap
//             adjListTakBeratap[u].push_back({v, w});
//             adjListTakBeratap[v].push_back({u, w});
//         }
//         else
//         {
//             outEdges[u].push_back({v, w});
//             outEdges[v].push_back({u, w});

//             inEdges[v].push_back({u, w});
//             inEdges[u].push_back({v, w});
//         }
//     }

//     int s = 1, t = n;

//     vector<ll> distBebas = dijkstra(adjList, s);
//     vector<ll> distTakBeratap = dijkstra(adjListTakBeratap, s);

//     int q;
//     cin >> q;
//     vector<ll> tt(q);
//     vector<int> perm(q);
//     for (int i = 0; i < q; i++)
//     {
//         cin >> tt[i];
//         perm[i] = i;
//     }

//     sort(perm.begin(), perm.end(), [&](int a, int b)
//          { return tt[a] < tt[b]; });

//     vector<int> newToOld(q);

//     vector<ll> sortedtt(q);
//     for (int i = 0; i < q; i++)
//     {
//         sortedtt[i] = tt[perm[i]];
//         newToOld[i] = perm[i];
//     }

//     vector<ll> res(q);

//     for (int i = 0; i < q; i++)
//     {
//         ll time = sortedtt[i];
//         if (distBebas[t] <= time)
//         {
//             res[newToOld[i]] = distBebas[t];
//         }
//         else
//         {
//             ll minCost = INF;
//             for (int mid = 1; mid < n + 1; mid++)
//             {
//                 if (distTakBeratap[mid] <= time)
//                 {
//                     ll cost1 = distTakBeratap[mid];
//                     auto cost2 = bidirectional_dijkstra(outEdges, inEdges, mid, t);
//                     minCost = min(minCost, cost1 + cost2);
//                 }
//             }

//             res[newToOld[i]] = minCost;
//         }
//     }

//     for (int i = 0; i < q; i++)
//     {
//         if (res[i] == INF)
//         {
//             cout << -1 << endl;
//         }
//         else
//         {
//             cout << res[i] << endl;
//         }
//     }
// }