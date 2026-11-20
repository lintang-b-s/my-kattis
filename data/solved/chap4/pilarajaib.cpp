#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pilar
{
    ll xi, yi, ri, ci;
};

struct interval
{
    ll left, right;
    int id;
};
// O(nlogn), n=len(intervals)
void sweep_line(vector<interval> intervals, vector<int> &comps)
{
    sort(intervals.begin(), intervals.end(), [](interval &a, interval &b)
         {
        if (a.left != b.left) {
            return a.left < b.left;
        }
        return a.right < b.right; });

    int compId = 0;
    ll curr_right = intervals[0].right;

    int n = intervals.size();
    for (int i = 0; i < n; i++)
    {
        if (intervals[i].left > curr_right)
        {
            curr_right = intervals[i].right;
            compId++;
        }
        curr_right = max(curr_right, intervals[i].right);
        comps[intervals[i].id] = compId;
    }
}

const ll INF = (ll)1 << 61;

ll dijkstra(vector<vector<pair<int, ll>>> adjList, int s, int t)
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

        if (u == t)
        {
            return uDist;
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

    return -1;
}

int main()
{
    ll n, xs, ys, xf, yf;
    cin >> n >> xs >> ys >> xf >> yf;
    // s=0 (sumber sinar), f=1 (titik akhir yang ingin disinari)
    int s = 0;
    int f = 1;

    int pilarIdOffset = 2;

    vector<interval> horIntervals, verIntervals;  // horizontal dan vertical intervals
    vector<int> horComps(n + 2), verComps(n + 2); // horizontal dan vertical components. map dari pilar/sinar id ke component id

    vector<pilar> pilars;

    horIntervals.push_back({ys, ys, 0});
    verIntervals.push_back({xs, xs, 0});

    horIntervals.push_back({yf, yf, 1});
    verIntervals.push_back({xf, xf, 1});

    for (int i = 0; i < n; i++)
    {
        ll xi, yi, ri, ci;
        cin >> xi >> yi >> ri >> ci;
        pilar pi{xi, yi, ri, ci};
        pilars.push_back(pi);

        int pid = pilarIdOffset + i;
        horIntervals.push_back({yi - ri, yi + ri, pid});
        verIntervals.push_back({xi - ri, xi + ri, pid});
    }

    sweep_line(horIntervals, horComps);
    sweep_line(verIntervals, verComps);

    // bikin graph dengan vertices nya horizontal & vertical components

    int m = horComps.size();
    vector<vector<pair<int, ll>>> adjList(n + 2 + m);

    for (int i = pilarIdOffset; i < n + 2; i++)
    {
        int pilarId = i - pilarIdOffset;
        adjList[horComps[i]].push_back({verComps[i] + m, pilars[pilarId].ci});
        adjList[verComps[i] + m].push_back({horComps[i], pilars[pilarId].ci});
    }

    ll biaya1 = dijkstra(adjList, horComps[0], horComps[1]);
    ll biaya2 = dijkstra(adjList, horComps[0], verComps[1] + m);
    if (biaya1 != -1 && biaya2 != -1)
    {
        cout << min(biaya1, biaya2) << endl;
    }
    else if (biaya1 != -1)
    {
        cout << biaya1 << endl;
    }
    else if (biaya2 != -1)
    {
        cout << biaya2 << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
