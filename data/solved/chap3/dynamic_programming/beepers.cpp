
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 2e9;

const int MAX_N = 11;

// get least significant bit
int LSONE(int S)
{
    return (S) & -(S);
}

/*
dp(S,j) minimum cost path start at karel coordinate 0, visit all beepers in the set S exactly once, 
ends at beeper j. j and karel in S. 

S is a subset of the set of all beepers + karel. there is 2^{n-1} possible subsets S that contain karel coordinate 0.
base case:
dp({0,j}, j)

recurrence:
dp(S,j) = min(dp(S\{j}, i) + w(i,j)), for all i != j


solution:
min(dp(V,j)+w(j,0)), for all j.


dpTSP compute minimum cost at vertex u and have visited all vertices described by off bit in mask.
time: O(2^{n-1}*n^2), number of subsets 2^{n-1} * number of possible value of j * O(n) works for each state
*/
int dpTSP(int u, int mask, int memo[MAX_N][1 << (MAX_N - 1)], int dist[MAX_N][MAX_N])
{
    if (mask == 0)
    {
        return dist[u][0];
    }
    int &ans = memo[u][mask];
    if (ans != -1)
    {
        return ans;
    }
    ans = INF;
    int m = mask;
    while (m)
    {
        int two_pow_v = LSONE(m);             // get least significant bit.
        int v = __builtin_ctz(two_pow_v) + 1; // 2^j=two_pow_v. return j + 1. skip karel
        ans = min(ans, dist[u][v] + dpTSP(v, mask ^ two_pow_v, memo, dist));
        m -= two_pow_v;
    }
    return ans;
}

int main()
{
    int scenarios;
    cin >> scenarios;
    for (int i = 0; i < scenarios; i++)
    {
        int xs, ys;
        cin >> xs >> ys;
        int karelx, karely;
        cin >> karelx >> karely;

        int n;
        cin >> n;
        vector<pair<int, int>> bepeerCoords;
        bepeerCoords.push_back({karelx, karely});
        for (int j = 0; j < n; j++)
        {
            int bx, by;
            cin >> bx >> by;
            bepeerCoords.push_back({bx, by});
        }

        n++;

        int dist[MAX_N][MAX_N];

        auto manhattan = [&](int xa, int ya, int xb, int yb)
        {
            return abs(xa - xb) + abs(ya - yb);
        };

        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                auto [xu, yu] = bepeerCoords[u];
                auto [xv, yv] = bepeerCoords[v];

                dist[u][v] = manhattan(xu, yu, xv, yv);
            }
        }
        int karolId = 0, mask = (1 << (n - 1)) - 1;

        int memo[MAX_N][1 << (MAX_N - 1)];
        memset(memo, -1, sizeof memo);
        cout << dpTSP(0, mask, memo, dist) << endl;
    }
}
