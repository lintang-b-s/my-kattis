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
    int n, q, s;
    cin >> n >> q >> s;
    vector<int> queueSensor(s);
    vector<int> queuesize(q);

    vector<vector<int>> downLinks(n, vector<int>(s));
    vector<int> downlinkData(n);
    for (int i = 0; i < s; i++)
    {
        cin >> queueSensor[i];
    }

    for (int i = 0; i < q; i++)
    {
        cin >> queuesize[i];
    }

    ll totGeneratedData = 0;

    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;
        downlinkData[i] = d;
        for (int j = 0; j < s; j++)
        {
            cin >> downLinks[i][j];
            totGeneratedData += downLinks[i][j];
        }
    }

    // vertices id:
    // source=0, target =1
    // all sensors s_1_1,..,s_s_n = 2,3,....,2+s*n-1  (sensor_1_window_1, sensor_2_window_1, .. ,sensor_s_window_n)
    // all in-queues q_1_1,.., q_q_n = 2+s*n, (2+s*n)+1, ..., (2+s*n)+q*n-1
    // all out-queues qo_1_1,..,qo_q_n = 2+s*n+q*n, (2+s*n+q*n)+1, ..., (2+s*n+q*n)+q*n-1
    // all in_downlink windows w_1,.. ,w_n = 2+s*n+q*n+q*n, (2+s*n+q*n+q*n)+1, .... , (2+s*n+q*n+q*n)+n-1
    // all out_downlink windows w_1,...,w_n = 2+s*n+q*n+q*n+n, (2+s*n+q*n+q*n+n)+1, ..., (2+s*n+q*n+q*n+n)+n-1

    int source = 0;
    int target = 1;
    maxFlow dinic((2 + s * n + q * n + q * n + n) + n);

    for (int window = 1; window <= n; window++)
    {
        for (int sensor = 1; sensor <= s; sensor++)
        {
            // source ke sensors
            dinic.add_edge(source, (window - 1) * s + sensor + 1, downLinks[window - 1][sensor - 1]);

            int qs = queueSensor[sensor - 1];
            // each sensors ke each in-queues in the same window,
            dinic.add_edge((window - 1) * s + sensor + 1, (window - 1) * q + (n * s + 1) + qs, INF);

            // setiap out-queue bisa kirim sisa data nya ke in-queue yang sama di next window downlink
        }

        for (int queuee = 1; queuee <= q; queuee++)
        {
            // in-queue ke out-queue
            dinic.add_edge((window - 1) * q + (n * s + 1) + queuee, (window - 1) * q + (n * s + q * n + 1) + queuee, queuesize[queuee - 1]);
            if (window + 1 <= n)
            {
                // edge out-queue  ke in-queue next window
                dinic.add_edge((window - 1) * q + (n * s + q * n + 1) + queuee, (window)*q + (n * s + 1) + queuee, INF);
            }

            // each out-queue  ke in-downlink satelites
            dinic.add_edge((window - 1) * q + (n * s + q * n + 1) + queuee, (n * s + 2 * q * n + 1) + window, INF);
        }

        // each in-downlink ke out-downlink
        dinic.add_edge((n * s + 2 * q * n + 1) + window, (n * s + 2 * q * n + n + 1) + window, downlinkData[window - 1]);

        // each out-downlink satelites ke target/bumi?
        dinic.add_edge((n * s + 2 * q * n + n + 1) + window, target, INF);
    }

    ll mf = dinic.findMaxFlow(source, target); // O(V^2*E), V=(2 + s * n + q * n + q * n + n) + n
    if (mf == totGeneratedData)
    {
        cout << "possible" << "\n";
    }
    else
    {
        cout << "impossible" << "\n";
    }
}
