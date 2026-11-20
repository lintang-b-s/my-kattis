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
    int s, r, f, t;
    cin >> s >> r >> f >> t;

    int vId = 2;
    unordered_map<string, int> states;
    unordered_map<string, int> suppliers;
    for (int i = 0; i < r; i++)
    {
        string st;
        cin >> st;
        suppliers[st] = vId;
        states[st] = vId;
        vId++;
    }

    unordered_map<string, int> pabrik;

    for (int i = 0; i < f; i++)
    {
        string namaPabrik;
        cin >> namaPabrik;
        pabrik[namaPabrik] = vId;
        states[namaPabrik] = vId;
        vId++;
    }

    vector<vector<string>> perusahaanTransportasi(t);
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++)
        {
            string st;
            cin >> st;

            perusahaanTransportasi[i].push_back(st);
            if ((!suppliers.count(st) || !pabrik.count(st)) && !states.count(st))
            {
                states[st] = vId;
                vId++;
            }
        }
    }

    maxFlow dinic(vId + 2 * t);

    for (int i = 0; i < t; i++)
    {
        int inTVId = vId;
        int outTVId = vId + 1;
        //  each transportation company handles the output of at most one raw material site and delivers to at most one factory
        dinic.add_edge(inTVId, outTVId, 1);

        for (int j = 0; j < perusahaanTransportasi[i].size(); j++)
        {
            auto state = perusahaanTransportasi[i][j];
            dinic.add_edge(states[state], inTVId, 1);
            dinic.add_edge(outTVId, states[state], 1);
        }

        vId += 2;
    }

    int source = 0;
    int sink = 1;

    for (auto [stateName, stateVId] : suppliers)
    {
        dinic.add_edge(source, stateVId, 1);
    }

    for (auto [pabrikName, pabrikVId] : pabrik)
    {
        dinic.add_edge(pabrikVId, sink, 1);
    }

    int mf = dinic.findMaxFlow(source, sink); // O(V^2*E)
    cout << mf << "\n";
}

// TLE
// int main()
// {
//     int s, r, f, t;
//     cin >> s >> r >> f >> t;

//     int vId = 2;
//     unordered_map<string, int> suppliers;
//     for (int i = 0; i < r; i++)
//     {
//         string st;
//         cin >> st;
//         suppliers[st] = vId;
//         vId++;
//     }

//     unordered_map<string, int> pabrik;

//     for (int i = 0; i < f; i++)
//     {
//         string namaPabrik;
//         cin >> namaPabrik;
//         pabrik[namaPabrik] = vId;
//         vId++;
//     }

//     unordered_map<string, int> intermediateStates;

//     vector<vector<string>> perusahaanTransportasi(t);
//     for (int i = 0; i < t; i++)
//     {
//         int n;
//         cin >> n;
//         for (int j = 0; j < n; j++)
//         {
//             string st;
//             cin >> st;

//             perusahaanTransportasi[i].push_back(st);
//             if (!suppliers.count(st))
//             {
//                 intermediateStates[st] = vId;
//                 vId++;
//             }
//         }
//     }

//     maxFlow dinic(vId);

//     for (int i = 0; i < t; i++)
//     {
//         for (int j = 0; j < perusahaanTransportasi[i].size(); j++)
//         {
//             string st1 = perusahaanTransportasi[i][j];
//             int node1;
//             if (!suppliers.count(st1) && intermediateStates.count(st1))
//             {
//                 node1 = intermediateStates[st1];
//             }
//             else if (suppliers.count(st1))
//             {
//                 node1 = suppliers[st1];
//             }

//             for (int k = j; k < perusahaanTransportasi[i].size(); k++)
//             {
//                 string st2 = perusahaanTransportasi[i][k];
//                 if (!pabrik.count(st2) && intermediateStates.count(st2))
//                 {
//                     int node2 = intermediateStates[st2];
//                     dinic.add_edge(node1, node2, 1);
//                 }
//                 else if (pabrik.count(st2))
//                 {

//                     int node2 = pabrik[st2];
//                     dinic.add_edge(node1, node2, 1);
//                 }
//             }
//         }
//     }

//     int source = 0;
//     int sink = 1;

//     for (auto [stateName, stateVId] : suppliers)
//     {
//         dinic.add_edge(source, stateVId, 1);
//     }

//     for (auto [pabrikName, pabrikVId] : pabrik)
//     {
//         dinic.add_edge(pabrikVId, sink, 1);
//     }

//     int mf = dinic.findMaxFlow(source, sink);
//     cout << mf << "\n";
// }