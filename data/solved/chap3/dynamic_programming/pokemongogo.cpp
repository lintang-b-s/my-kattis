#include <bits/stdc++.h>
using namespace std;

const int MAX_STOPS = 21; // n + my location
const int MAX_POKE = 16;
const int INF = 2e9;

int dpTSP(int u, int mask, int dp[MAX_STOPS][(1 << (MAX_POKE - 1))], int dist[MAX_STOPS][MAX_STOPS], vector<int> stopMasks)
{
    if (mask == 0)
    {
        return dist[u][0];
    }

    int &ans = dp[u][mask];
    if (ans != -1)
    {
        return ans;
    }

    int m = stopMasks.size();
    ans = INF;

    for (int v = 1; v < m; v++)
    {
        if ((mask & (stopMasks[v])) == 0)
        {
            continue;
        }

        int nextMask = mask ^ stopMasks[v];

        ans = min(ans, dist[u][v] + dpTSP(v, nextMask, dp, dist, stopMasks));
    }

    return ans;
}

int main()
{

    int n;
    cin >> n;

    unordered_map<string, int> pokemonId;

    map<pair<int, int>, vector<string>> stops;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        string poke;

        cin >> x >> y >> poke;

        stops[{x, y}].push_back(poke);

        if (!pokemonId.count(poke))
        {
            int id = pokemonId.size();
            pokemonId[poke] = id;
        }
    }

    vector<int> stopMasks;
    vector<pair<int, int>> locations;
    locations.push_back({0, 0});
    stopMasks.push_back(0);

    for (auto &entry : stops)
    {
        int x = entry.first.first;
        int y = entry.first.second;

        int mask = 0;

        for (auto &poke : entry.second)
            mask |= (1 << pokemonId[poke]);

        locations.push_back({x, y});
        stopMasks.push_back(mask);
    }

    int m = locations.size();

    int dist[MAX_STOPS][MAX_STOPS];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dist[i][j] =
                abs(locations[i].first - locations[j].first) +
                abs(locations[i].second - locations[j].second);
        }
    }

    int numPokemons = pokemonId.size() + 1;

    int dp[MAX_STOPS][(1 << (MAX_POKE - 1))];
    memset(dp, -1, sizeof dp);
    int mask = (1 << (numPokemons - 1)) - 1;
    cout << dpTSP(0, mask, dp, dist, stopMasks) << endl;
}

