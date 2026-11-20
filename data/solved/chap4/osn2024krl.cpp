#include <bits/stdc++.h>
using namespace std;

typedef long long valType;
class SegmentTree
{
private:
    int n;
    vector<valType> A, st, lazy;
    bool minimum;

    int leftChild(int parent)
    {
        // go to left child
        return parent << 1;
    }

    int rightChild(int parent)
    {
        return (parent << 1) + 1;
    }

    valType conquer(valType a, valType b)
    {
        if (a == -1)
        {
            return b;
        }
        if (b == -1)
        {
            return a;
        }
        if (minimum)
        {
            return min(a, b);
        }
        return max(a, b);
    }

    void build(int parent, int L, int R)
    { // O(n)
        if (L == R)
        {
            st[parent] = A[L];
        }
        else
        {
            int mid = (L + R) / 2;
            build(leftChild(parent), L, mid);
            build(rightChild(parent), mid + 1, R);
            st[parent] = conquer(st[leftChild(parent)], st[rightChild(parent)]);
        }
    }

    void propagate(int parent, int L, int R)
    {
        if (lazy[parent] != -1)
        { // parent has a lazy flag
            st[parent] = lazy[parent];

            if (L != R)
            {
                lazy[leftChild(parent)] = lazy[rightChild(parent)] = lazy[parent];
            }
            else
            {
                A[L] = lazy[parent];
            }
            lazy[parent] = -1;
        }
    }

    valType RMQ(int parent, int L, int R, int i, int j)
    { // O(log N)
        propagate(parent, L, R);
        if (i > j)
        {
            return -1;
        }
        if ((i <= L) && (j >= R))
        {
            return st[parent];
        }

        int mid = (L + R) / 2;
        return conquer(RMQ(leftChild(parent), L, mid, i, min(mid, j)),
                       RMQ(rightChild(parent), mid + 1, R, max(i, mid + 1), j));
    }

    void update(int parent, int L, int R, int i, int j, valType val)
    {
        propagate(parent, L, R);

        if (i > j)
        {
            return;
        }
        if ((i <= L) && (j >= R))
        {
            lazy[parent] = val;
            propagate(parent, L, R);
        }
        else
        {
            int mid = (L + R) / 2;
            update(leftChild(parent), L, mid, i, min(mid, j), val);
            update(rightChild(parent), mid + 1, R, max(i, mid + 1), j, val);
            valType leftSubTree = (lazy[leftChild(parent)] != -1) ? lazy[leftChild(parent)] : st[leftChild(parent)];
            valType rightSubTree = (lazy[rightChild(parent)] != -1) ? lazy[rightChild(parent)] : st[rightChild(parent)];
            st[parent] = conquer(leftSubTree, rightSubTree);
        }
    }

public:
    SegmentTree(int size, bool isMinimum) : n(size), A(n), st(4 * n), lazy(4 * n, -1), minimum(isMinimum) {}

    SegmentTree(vector<valType> &initialA, bool isMinimum) : SegmentTree(initialA.size(), isMinimum)
    {
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, valType val)
    {
        update(1, 0, n - 1, i, j, val);
    }

    valType RMQ(int i, int j)
    { // get index of max/min value over arr[i], arr[i+1], ... ,arr[j]
        return RMQ(1, 0, n - 1, i, j);
    }
};

typedef long long ll;
struct rute
{
    ll a, b, c, d;
};

const ll INF = 1e15;

int main()
{
    ll N, M, K, T, P, Q;
    cin >> N >> M >> K >> T >> P >> Q;

    vector<rute> rutes(M);
    for (int i = 0; i < M; i++)
    {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        rutes[i] = rute{a, b, c, d};
    }

    vector<vector<pair<int, ll>>> adjList(2 * N);

    SegmentTree st(N, true);

    sort(rutes.begin(), rutes.end(), [&](rute a, rute b)
         { return a.c > b.c; }); // O(MlogM)

    for (int i = 0; i < M; i++)
    { // O(M * log N)
        auto rt = rutes[i];
        // set minimum cost edges dari sistem komuter.
        // A[0] = edge{0,1}, A[1] = edge{1,2},....
        st.update(rt.a - 1, rt.b - 2, rt.c); // O(logN)
    }

    for (int i = 0; i < M; i++)
    {
        auto rt = rutes[i];
        int a = rt.a - 1 + N;
        int b = rt.b - 1 + N;

        // edges sistem ekspress
        adjList[a].push_back({b, rt.d});
        adjList[b].push_back({a, rt.d});
    }

    for (int v = 0; v < N; v++)
    {
        // edge non-transit vertex ke transit vertex
        adjList[v].push_back({v + N, T});
        // edge vertex ke non-transit vertex
        adjList[v + N].push_back({v, 0});
    }

    for (int v = 0; v + 1 < N; v++)
    { // O(N *logN)
        // angkot
        // stasiun non-transit ke next stasiun non-transit
        adjList[v].push_back({v + 1, K});
        adjList[v + 1].push_back({v, K});

        ll rmqv = st.RMQ(v, v); // O(logN)

        if (rmqv == 0)
        {
            continue;
        }
        // commuter edges
        adjList[v + N].push_back({v + 1 + N, rmqv});
        adjList[v + 1 + N].push_back({v + N, rmqv});
    }

    P--;
    Q--;

    unordered_map<ll, ll> dist(2 * N);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    dist[P] = 0;
    pq.emplace(0, P);

    while (!pq.empty())
    { // O((W+N)logN) , W = number of edges
        auto [uDist, u] = pq.top();
        pq.pop();

        if (dist.count(u) && uDist > dist[u])
        {
            continue;
        }

        for (auto [v, vDist] : adjList[u])
        {
            if (!dist.count(v) || (dist.count(v) && uDist + vDist < dist[v]))
            {
                dist[v] = uDist + vDist;
                pq.emplace(dist[v], v);
            }
        }
    }

    if (dist[Q] < dist[Q + N])
    {
        cout << dist[Q] << "\n";
    }
    else
    {
        cout << dist[Q + N] << "\n";
    }
}

// MLE, keknya bisa pakai segment tree buat kurangi edges sistem komuter yang redundan
// int main()
// {
//     ll N, M, K, T, P, Q;
//     cin >> N >> M >> K >> T >> P >> Q;

//     vector<rute> rutes(M);
//     for (int i = 0; i < M; i++)
//     {
//         ll a, b, c, d;
//         cin >> a >> b >> c >> d;
//         rutes[i] = rute{a, b, c, d};
//     }

//     vector<vector<pair<int, ll>>> adjList(2 * N);

//     for (int i = 0; i < M; i++)
//     {
//         auto rt = rutes[i];
//         int a = rt.a - 1 + N; // 0 + N = N
//         int b = rt.b - 1 + N; // N-1 + N = 2N-1

//         // edges sistem ekspress
//         adjList[a].push_back({b, rt.d});
//         adjList[b].push_back({a, rt.d});

//         for (int j = a; j < b; j++)
//         { // edges sistem komuter
//             adjList[j].push_back({j + 1, rt.c}); // redundan
//             adjList[j + 1].push_back({j, rt.c});
//         }
//     }

//     for (int v = 0; v < N; v++)
//     {
//         // edge non-transit vertex ke transit vertex
//         adjList[v].push_back({v + N, T});
//         // edge vertex ke non-transit vertex
//         adjList[v + N].push_back({v, 0});
//     }

//     for (int v = 0; v + 1 < N; v++)
//     {
//         // angkot
//         // stasiun non-transit ke next stasiun non-transit
//         adjList[v].push_back({v + 1, K});
//         adjList[v + 1].push_back({v, K});
//     }

//     P--;
//     Q--;

//     vector<ll> dist(2 * N, INF);
//     priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

//     dist[P] = 0;
//     pq.emplace(0, P);

//     while (!pq.empty())
//     {
//         auto [uDist, u] = pq.top();
//         pq.pop();

//         if (uDist > dist[u])
//         {
//             continue;
//         }

//         for (auto [v, vDist] : adjList[u])
//         {
//             if (uDist + vDist < dist[v])
//             {
//                 dist[v] = uDist + vDist;
//                 pq.emplace(dist[v], v);
//             }
//         }
//     }

//     if (dist[Q] < dist[Q + N])
//     {
//         cout << dist[Q] << "\n";
//     }
//     else
//     {
//         cout << dist[Q + N] << "\n";
//     }
// }