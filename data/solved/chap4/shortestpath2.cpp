#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/shortestpath2?tab=metadata

int main()
{
    struct edge
    {
        int v;
        int t0;
        int P;
        int d;
    };

    int n, m, q, s;
    while (cin >> n >> m >> q >> s)
    {
        if (n == 0 && m == 0 && q == 0 && s == 0)
        {
            break;
        }
        vector<vector<edge>> adjList(n);
        for (int i = 0; i < m; i++)
        {
            int u, v, t0, P, d;
            cin >> u >> v >> t0 >> P >> d;
            adjList[u].push_back(edge{v, t0, P, d});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        unordered_map<int, int> elapsedTime;

        elapsedTime[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty())
        { // O((n+m) log n)
            auto [uTime, uId] = pq.top();
            pq.pop();
            if (elapsedTime.count(uId) && uTime > elapsedTime[uId])
            {
                continue;
            }

            for (auto e : adjList[uId])
            {
                if (uTime > e.t0)
                {
                    if (e.P == 0)
                    {
                        continue;
                    }

                    int t = (uTime - e.t0) / e.P;
                    int nextTime = e.t0 + t * e.P;
                    if (nextTime < uTime)
                    {
                        nextTime += e.P;
                    }

                    if (!elapsedTime.count(e.v) ||
                        (elapsedTime.count(e.v) &&
                         nextTime + e.d < elapsedTime[e.v]))
                    {
                        elapsedTime[e.v] = nextTime + e.d;
                        pq.emplace(elapsedTime[e.v], e.v);
                    }
                }
                else
                {
                    // e.t0 >= uTime

                    int selisihTime = e.t0 - uTime;

                    int newTimeTravel = elapsedTime[uId] + e.d + selisihTime;
                    if (!elapsedTime.count(e.v) ||
                        (elapsedTime.count(e.v) &&
                         newTimeTravel < elapsedTime[e.v]))
                    {
                        elapsedTime[e.v] = newTimeTravel;
                        pq.emplace(elapsedTime[e.v], e.v);
                    }
                }
            }
        }

        for (int i = 0; i < q; i++)
        {
            int t;
            cin >> t;
            if (elapsedTime.count(t))
            {
                cout << elapsedTime[t] << "\n";
            }
            else
            {
                cout << "Impossible" << "\n";
            }
        }
        cout << "\n";
    }
}