#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);
typedef long double ld;
int main()
{

    int h, w;
    cin >> h >> w;
    vector<vector<char>> peta(h, vector<char>(w, ' '));

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cin >> peta[i][j];
        }
    }

    vector<vector<pair<int, ld>>> adjList(h * w * 4 + 2);

    double seperempatDiam = 2.5 * PI;

    auto cellToNId = [&h, w](int i, int j, int nodeid)
    {
        return i * w + j + 3 * (w * i + j) + nodeid;
    };

    int vid = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            auto cur = peta[i][j];
            if (cur == 'X')
            {
                int i0 = cellToNId(i, j, 0);
                int i1 = cellToNId(i, j, 1);
                int i2 = cellToNId(i, j, 2);
                int i3 = cellToNId(i, j, 3);

                // cur tower = tower kotak
                // buat edge ke 4 node dari x, atas kanan kiri bawah persegi
                adjList[i0].push_back({i1, 10});
                adjList[i1].push_back({i2, 10});
                adjList[i2].push_back({i3, 10});
                adjList[i3].push_back({i0, 10});

                adjList[i1].push_back({i0, 10});
                adjList[i2].push_back({i1, 10});
                adjList[i3].push_back({i2, 10});
                adjList[i0].push_back({i3, 10});

                if (j + 1 < w)
                {

                    int j10 = cellToNId(i, j + 1, 0);
                    int j11 = cellToNId(i, j + 1, 1);
                    int j12 = cellToNId(i, j + 1, 2);
                    int j13 = cellToNId(i, j + 1, 3);

                    // buat edge ke tower kanan
                    auto kanan = peta[i][j + 1];
                    if (kanan == 'O')
                    {
                        adjList[i0].push_back({j10, 10});
                        adjList[i1].push_back({j13, 0});
                        adjList[i2].push_back({j12, 10});
                    }
                    else
                    {
                        adjList[i0].push_back({j10, 10});
                        adjList[i1].push_back({j13, 0});
                        adjList[i2].push_back({j12, 10});
                    }
                }

                if (i + 1 < h)
                {
                    int i10 = cellToNId(i + 1, j, 0);
                    int i11 = cellToNId(i + 1, j, 1);
                    int i12 = cellToNId(i + 1, j, 2);
                    int i13 = cellToNId(i + 1, j, 3);

                    // buat edge ke tower bawah
                    auto bawah = peta[i + 1][j];
                    if (bawah == 'O')
                    {
                        adjList[i2].push_back({i10, 0});
                        adjList[i3].push_back({i13, 10});
                        adjList[i1].push_back({i11, 10});
                    }
                    else
                    {
                        adjList[i2].push_back({i10, 0});
                        adjList[i3].push_back({i13, 10});
                        adjList[i1].push_back({i11, 10});
                    }
                }
            }
            else
            {
                // cur tower = tower bundar
                // buat edge ke 4 node dari o, atas kanan kiri bawah pas lingkaran
                int i0 = cellToNId(i, j, 0);
                int i1 = cellToNId(i, j, 1);
                int i2 = cellToNId(i, j, 2);
                int i3 = cellToNId(i, j, 3);

                adjList[i0].push_back({i1, seperempatDiam});
                adjList[i1].push_back({i2, seperempatDiam});
                adjList[i2].push_back({i3, seperempatDiam});
                adjList[i3].push_back({i0, seperempatDiam});

                adjList[i1].push_back({i0, seperempatDiam});
                adjList[i2].push_back({i1, seperempatDiam});
                adjList[i3].push_back({i2, seperempatDiam});
                adjList[i0].push_back({i3, seperempatDiam});

                if (j + 1 < w)
                {
                    int j10 = cellToNId(i, j + 1, 0);
                    int j11 = cellToNId(i, j + 1, 1);
                    int j12 = cellToNId(i, j + 1, 2);
                    int j13 = cellToNId(i, j + 1, 3);

                    // buat edge ke tower kanan
                    auto kanan = peta[i][j + 1];
                    if (kanan == 'O')
                    {
                        adjList[i0].push_back({j10, 10});

                        adjList[i1].push_back({j13, 0});

                        adjList[i2].push_back({j12, 10});
                    }
                    else
                    {
                        adjList[i0].push_back({j10, 10});
                        adjList[i1].push_back({j13, 0});
                        adjList[i2].push_back({j12, 10});
                    }
                }

                if (i + 1 < h)
                {
                    int i10 = cellToNId(i + 1, j, 0);
                    int i11 = cellToNId(i + 1, j, 1);
                    int i12 = cellToNId(i + 1, j, 2);
                    int i13 = cellToNId(i + 1, j, 3);
                    // buat edge ke tower bawah
                    auto bawah = peta[i + 1][j];
                    if (bawah == 'O')
                    {
                        adjList[i2].push_back({i10, 0});

                        adjList[i3].push_back({i13, 10});

                        adjList[i1].push_back({i11, 10});
                    }
                    else
                    {
                        adjList[i2].push_back({i10, 0});
                        adjList[i3].push_back({i13, 10});
                        adjList[i1].push_back({i11, 10});
                    }
                }
            }
        }
    }
 
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>> pq;
    unordered_map<int, ld> dist;

    int s = h * w * 4;
    int t = h * w * 4 + 1;

    adjList[s].push_back({cellToNId(0, 0, 0), 5.0});

    adjList[s].push_back({cellToNId(0, 0, 3), 5.0});

    int last1 = cellToNId(h - 1, w - 1, 1);
    int last2 = cellToNId(h - 1, w - 1, 2);

    adjList[last1].push_back({t, 5.0});

    adjList[last2].push_back({t, 5.0});

    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty())
    {
        auto [uDist, u] = pq.top();
        pq.pop();

        if (uDist > dist[u])
        {
            continue;
        }

        for (auto [v, vDist] : adjList[u])
        {
            if (!dist.count(v) || (dist.count(v) && dist[u] + vDist < dist[v]))
            {
                dist[v] = dist[u] + vDist;
                pq.emplace(dist[v], v);
            }
        }
    }

    cout.precision(12);
    cout << dist[t] << "\n";
}