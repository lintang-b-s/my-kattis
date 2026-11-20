#include <bits/stdc++.h>
using namespace std;

int LSONE(int S) // get least significant bit
{
    return S & -(S);
}
// https://codeforces.com/gym/100753/attachments
typedef long long ll;

struct place
{
    int v, stayTime;
};

const ll INF = 4e18;

vector<ll> dijkstra(vector<vector<pair<int, ll>>> &adjList, int s)
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

const int MAX_N = 15;

/*
dp(S,j) minimum cost path start at athens coordinate 0, visit all places in the set S exactly once,
ends at place j. j and athens in S.

S is a subset of the set of all places + athens. there is 2^{n-1} possible subsets S that contain athens coordinate 0.
base case:
dp({0,j}, j)

recurrence:
dp(S,j) = min(dp(S\{j}, i) + w(i,j)), for all i != j


solution:
min(dp(V,j)+w(j,0)), for all j.


dpTSP compute minimum cost at vertex u and have visited all vertices described by off bit in mask.
time: O(2^{n-1}*n^2), number of subsets 2^{n-1} * number of possible value of j * O(n) works for each state
*/
ll dpTSP(int u, int mask, ll dp[MAX_N][1 << (MAX_N - 1)], ll dist[MAX_N][MAX_N])
{

    if (mask == 0)
    {

        return dist[u][0];
    }

    ll &ans = dp[u][mask];
    if (ans != -1)
    {
        return ans;
    }

    ans = INF;
    int m = mask;
    while (m)
    {
        int two_pow_v = LSONE(m);             // least significant bit
        int v = __builtin_ctz(two_pow_v) + 1; // 2^j=two_pow_v, get j+1
        ans = min(ans, dist[u][v] + dpTSP(v, mask ^ two_pow_v, dp, dist));
        m -= two_pow_v;
    }

    return ans;
}

ll dpTSPWithTaxi(int u, int mask, ll dp[MAX_N][1 << (MAX_N - 1)][2], ll dist[MAX_N][MAX_N], bool usedTaxi, ll taxiTime)
{

    if (mask == 0)
    {

        ll ans = dist[u][0];
        if (!usedTaxi)
        {
            ans = min(ans, taxiTime);
        }
        return ans;
    }

    ll &ans = dp[u][mask][usedTaxi];
    if (ans != -1)
    {
        return ans;
    }

    ans = INF;
    int m = mask;
    while (m)
    {
        int two_pow_v = LSONE(m);             // least significant bit
        int v = __builtin_ctz(two_pow_v) + 1; // 2^j=two_pow_v, get j+1
        ans = min(ans, dist[u][v] + dpTSPWithTaxi(v, mask ^ two_pow_v, dp, dist, usedTaxi, taxiTime));
        if (!usedTaxi)
        {
            ans = min(ans, taxiTime + dpTSPWithTaxi(v, mask ^ two_pow_v, dp, dist, true, taxiTime));
        }
        m -= two_pow_v;
    }

    return ans;
}

int main()
{
    int n, p, m, g, t;
    cin >> n >> p >> m >> g >> t;

    vector<place> placeStay(p);
    for (int i = 0; i < p; i++)
    {
        int v, stayTime;
        cin >> v >> stayTime;
        placeStay[i] = {v, stayTime};
    }

    vector<vector<pair<int, ll>>> adjList(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    ll dist[MAX_N][MAX_N];
    auto sDist = dijkstra(adjList, 0);

    int totalStayTime = 0;

    for (int i = 0; i < p; i++)
    {
        auto place = placeStay[i];
        auto curDist = dijkstra(adjList, place.v);
        int pvDist[MAX_N];
        for (int v = 0; v < curDist.size(); v++)
        {
            for (int j = 0; j < p; j++)
            {
                if (placeStay[j].v == v)
                {
                    dist[i + 1][j + 1] = curDist[v];
                }
                else if (v == 0)
                {
                    dist[i + 1][0] = curDist[v];
                }
            }
        }
        dist[0][i + 1] = sDist[place.v];
        totalStayTime += place.stayTime;
    }

    ll dp[MAX_N][1 << (MAX_N - 1)];

    memset(dp, -1, sizeof dp);
    ll withoutTaxi = dpTSP(0, (1 << p) - 1, dp, dist) + totalStayTime;

    ll dpTaxi[MAX_N][1 << (MAX_N - 1)][2];

    memset(dpTaxi, -1, sizeof dpTaxi);
    ll withTaxi = dpTSPWithTaxi(0, (1 << p) - 1, dpTaxi, dist, false, t) + totalStayTime;

    if (withoutTaxi <= g)
    {
        cout << "possible without taxi" << endl;
    }
    else if (withTaxi <= g)
    {
        cout << "possible with taxi" << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
}