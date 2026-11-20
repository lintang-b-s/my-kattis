#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;
class maxFlow
{
private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool bfs(int s, int t)
    {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == t)
            {
                break;
            }
            for (auto &idx : AL[u])
            {
                auto &[v, cap, flow] = EL[idx];
                if ((cap - flow) > 0 && (d[v] == -1))
                {
                    d[v] = d[u] + 1;
                    q.push(v);
                    p[v] = {u, idx};
                }
            }
        }
        return d[t] != -1;
    }

    ll dfs(int u, int t, ll f = INF)
    {
        if ((u == t) || (f == 0))
        {
            return f;
        }
        for (int &i = last[u]; i < (int)AL[u].size(); i++)
        {
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1)
            {
                continue;
            }
            if (ll pushed = dfs(v, t, min(f, cap - flow)))
            {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    maxFlow(int initialV) : V(initialV)
    {
        EL.clear();
        AL.assign(V, vi());
    }

    void add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v)
        {
            return;
        }
        EL.emplace_back(v, w, 0);
        AL[u].push_back(EL.size() - 1);
        EL.emplace_back(u, directed ? 0 : w, 0);
        AL[v].push_back(EL.size() - 1);
    }

    ll findMaxFlow(int s, int t)
    { // O(V^2 * E)
        ll mf = 0;
        while (bfs(s, t))
        {
            last.assign(V, 0);
            while (ll f = dfs(s, t))
            {
                mf += f;
            }
        }
        return mf;
    }

    vector<edge> getEdges()
    {
        return EL;
    }

    vector<vi> getAdjacencyList()
    {
        return AL;
    }
};

int main()
{
    int R, C;
    cin >> R >> C;

    vector<vector<ll>> kingdom(R, vector<ll>(C));
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> kingdom[i][j];
        }
    }

    // multi-sources nya ada di luar border kanan kiri atas (gabisa diagonal)
    // tinggal cari maxflow/mincut dari multisources(semua posisi lawan) ke castle out vertex(sink)
    // vertices id:
    // karena ini vertices with capacity kita harus splice jadi 2 vertices: (vertex-in, vertex-out)
    // for each cell (i,j) , verticeId = (i*m+j, r*c+i*m+j)
    // source=castle_i*m+ castle_j
    // for each sources:
    // sources atas, diatas border kingdom, ada C sources: R*C+R*C+k, for each 1<=k<=C
    // sources kiri, dikiri border kingdom, ada R sources: R*C+R*C+C+k, for each 1<=k<=R
    // sources kanan, dikanan border kingdom, ada R sources: R*C+R*C+C+R+k, for each 1<=k<=R
    // sources bawah, dibawah border kingdom, ada C sources: R*C+R*C+C+R+R+k, for each 1<=k<=C

    maxFlow dinic(R * C + R * C + C + R + R + C + 1);
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            int inVId = i * C + j;
            int outVId = R * C + i * C + j;

            dinic.add_edge(inVId, outVId, kingdom[i][j]);

            if (i + 1 <= R - 1)
            {
                int bawahInVid = (i + 1) * C + j;
                dinic.add_edge(outVId, bawahInVid, kingdom[i + 1][j]);
            }

            if (j + 1 <= C - 1)
            {
                int kananVId = (i)*C + (j + 1);
                dinic.add_edge(outVId, kananVId, kingdom[i][(j + 1)]);
            }

            if (i - 1 >= 0)
            {
                int atasVId = (i - 1) * C + j;
                dinic.add_edge(outVId, atasVId, kingdom[i - 1][j]);
            }

            if (j - 1 >= 0)
            {
                int kiriVId = i * C + (j - 1);
                dinic.add_edge(outVId, kiriVId, kingdom[i][j - 1]);
            }
        }
    }

    // dari posisi enemies ke border army kerajaan

    // karena multi-sources kita harus tambah artificial source, dan tambahkan edges dari supersource ke semua sources degnan INF weight
    int superSource = R * C + R * C + C + R + R + C;
    // atas
    for (int k = 1; k <= C; k++)
    {
        int musuhVId = R * C + R * C + k;
        int pasukanAtasInVId = k;
        dinic.add_edge(musuhVId, pasukanAtasInVId, INF);
        dinic.add_edge(superSource, musuhVId, INF);
    }

    // bawah
    for (int k = 1; k <= C; k++)
    {
        int musuhVId = R * C + R * C + C + R + R + k;
        int pasukanBawahInVId = (R - 1) * C + k;
        dinic.add_edge(musuhVId, pasukanBawahInVId, INF);
        dinic.add_edge(superSource, musuhVId, INF);
    }

    // kiri
    for (int k = 1; k <= R; k++)
    {
        int musuhVId = R * C + R * C + C + k;
        int pasukanKiriInVId = k * C + 0;
        dinic.add_edge(musuhVId, pasukanKiriInVId, INF);
        dinic.add_edge(superSource, musuhVId, INF);
    }

    // kanan
    for (int k = 1; k <= R; k++)
    {
        int musuhVId = R * C + R * C + C + R + k;
        int pasukanKananInVId = k * C + (C - 1);
        dinic.add_edge(musuhVId, pasukanKananInVId, INF);
        dinic.add_edge(superSource, musuhVId, INF);
    }

    int castlei, castlej;
    cin >> castlei >> castlej;
    int castleOutVId = R * C + (castlei * C + castlej);

    ll mf = dinic.findMaxFlow(superSource, castleOutVId);
    cout << mf << "\n";
}