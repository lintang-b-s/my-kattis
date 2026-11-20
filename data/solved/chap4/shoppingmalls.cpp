#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/shoppingmalls?tab=metadata
typedef long long ll;
struct place
{
    ll floor;
    ll x, y;
};
typedef long double ld;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<place> places(N);

    for (int i = 0; i < N; i++)
    {
        ll fl, x, y;
        cin >> fl >> x >> y;
        places[i] = place{fl * 5, x, y}; // distance between floors is 5m
    }

    vector<vector<pair<ll, ld>>> adjList(N);

    auto getDist = [](place placeA, place placeB, string type) -> pair<ld, ld>
    {
        ld ff = (placeA.floor - placeB.floor);
        ld xx = (placeA.x - placeB.x);
        ld yy = (placeA.y - placeB.y);
        ld dist = sqrt(ff * ff + xx * xx + yy * yy);
        if (type == "walking" || type == "stairs")
        {

            return {dist, dist};
        }
        else if (type == "lift")
        {
            return {(ld)1, (ld)1};
        }

        // escalator
        return {(ld)1, (ld)dist * (ld)3};
    };

    for (int i = 0; i < M; i++)
    {
        int a, b;
        string type;
        cin >> a >> b >> type;
        auto placeA = places[a];
        auto placeB = places[b];

        auto [distAB, distBA] = getDist(placeA, placeB, type);
        adjList[a].push_back({b, distAB});
        adjList[b].push_back({a, distBA});
    }

    auto dijkstra = [&adjList](int a, int b) -> vector<ll>
    {
        unordered_map<ll, ld> dist;
        priority_queue<pair<ld, ll>, vector<pair<ld, ll>>, greater<pair<ld, ll>>> pq;
        unordered_map<ll, ll> par;

        dist[a] = 0;
        pq.emplace(0, a);
        par[a] = -1;

        while (!pq.empty())
        { // O((m+n) log n), m=jumlah edges
            auto [uDist, u] = pq.top();
            pq.pop();
            if (uDist > dist[u])
            {
                continue;
            }

            if (u == b)
            {
                break;
            }

            for (auto [v, vDist] : adjList[u])
            {
                if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
                {
                    dist[v] = uDist + vDist;
                    pq.emplace(dist[v], v);
                    par[v] = u;
                }
            }
        }

        vector<ll> path(0);
        auto cur = b;
        while (cur != -1)
        {
            path.push_back(cur);
            cur = par[cur];
        }

        reverse(path.begin(), path.end());

        return path;
    };

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        auto path = dijkstra(a, b);
        for (int k = 0; k < path.size(); k++)
        { // worst case O(n)
            cout << path[k];
            if (k < path.size() - 1)
            {
                cout << " ";
            }
        }

        cout << "\n";
    }
}