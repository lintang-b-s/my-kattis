#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/worstweather?tab=metadata

typedef long long ll;
class SegmentTree
{
private:
    int n;
    vector<ll> A, st, lazy;
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

    int conquer(ll a, ll b)
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

    ll RMQ(int parent, int L, int R, int i, int j)
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

    void update(int parent, int L, int R, int i, int j, ll val)
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
            ll leftSubTree = (lazy[leftChild(parent)] != -1) ? lazy[leftChild(parent)] : st[leftChild(parent)];
            ll rightSubTree = (lazy[rightChild(parent)] != -1) ? lazy[rightChild(parent)] : st[rightChild(parent)];
            st[parent] = conquer(leftSubTree, rightSubTree);
        }
    }

public:
    SegmentTree(int size, bool isMinimum) : n(size), A(n), st(4 * n), lazy(4 * n, -1), minimum(isMinimum) {}

    SegmentTree(vector<ll> &initialA, bool isMinimum) : SegmentTree(initialA.size(), isMinimum)
    {
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, ll val)
    {
        update(1, 0, n - 1, i, j, val);
    }

    int RMQ(int i, int j)
    {
        return RMQ(1, 0, n - 1, i, j);
    }
};

int lowerBoundBinarySearch(vector<ll> arr, int l, int r, ll val)
{

    int res = arr.size();
    while (l <= r)
    {
        int mid = (l + r) / 2;

        if (arr[mid] >= val)
        {
            res = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return res;
}

int main()
{
    int n, m;

    while (scanf("%d", &n))
    {
        if (n == 0)
        {
            break;
        }

        vector<ll> rainfalls(0), years(0);
        for (int i = 0; i < n; i++)
        {
            ll year, yearRainfall;
            scanf("%lld %lld", &year, &yearRainfall);
            years.push_back(year);
            rainfalls.push_back(yearRainfall);
        }

        SegmentTree st(rainfalls, false);

        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        { // O(m * log N)
            int y, x;
            scanf("%lld %lld", &y, &x);
            int left = lower_bound(years.begin(), years.end(), y) - years.begin(); // O(log N)
            int right = lower_bound(years.begin(), years.end(), x) - years.begin();
            // rz >= rx && rz >=ry -> false
            bool yExists = left < n && years[left] == y;
            bool xExists = right < n && years[right] == x;

            if (!yExists && !xExists)
            {
                cout << "maybe" << "\n";
            }
            else if (!xExists)
            {
                ll maxRainfallBetweenYX = st.RMQ(left + 1, right - 1); // O(log N)

                if (maxRainfallBetweenYX >= rainfalls[left])
                {
                    cout << "false" << "\n";
                }
                else
                {
                    cout << "maybe" << "\n";
                }
            }
            else if (!yExists)
            {
                ll maxRainfallBetweenYX = st.RMQ(left, right - 1); // O(log N)
                // year[left] = lowerbound dari y

                if (maxRainfallBetweenYX >= rainfalls[right])
                {
                    cout << "false" << "\n";
                }
                else
                {
                    cout << "maybe" << "\n";
                }
            }
            else
            {
                ll maxRainfallBetweenYX = st.RMQ(left + 1, right - 1); // O(log N)

                if (rainfalls[right] > rainfalls[left])
                {
                    cout << "false" << "\n";
                }
                else if (maxRainfallBetweenYX >= rainfalls[right])
                {
                    cout << "false" << "\n";
                }
                else

                {
                    if (right - left == x - y)
                    {
                        cout << "true" << "\n";
                    }
                    else
                    {
                        cout << "maybe" << "\n";
                    }
                }
            }
        }
    }

    // WA
    // while (scanf("%d", &n))
    // {
    //     if (n == 0)
    //     {
    //         break;
    //     }

    //     vector<ll> rainfalls(0);
    //     unordered_map<ll, int> years(0);
    //     for (int i = 0; i < n; i++)
    //     {
    //         ll year, yearRainfall;
    //         scanf("%d %d", &year, &yearRainfall);
    //         years[year] = i;
    //         rainfalls.push_back(yearRainfall);
    //     }

    //     SegmentTree st(rainfalls, false);

    //     scanf("%d", &m);
    //     for (int i = 0; i < m; i++)
    //     {
    //         int y, x;
    //         scanf("%d %d", &y, &x);
    //         int left = -1;
    //         int right = -1;
    //         if (years.count(y))
    //         {
    //             left = years[y];
    //         }

    //         if (years.count(x))
    //         {
    //             right = years[x];
    //         }

    //         // rz >= rx && rz >=ry -> false

    //         if (right == -1 && left == -1)
    //         {
    //             cout << "maybe" << "\n";
    //         }
    //         else if (left == -1)
    //         {
    //             ll maxRainfallBetweenYX = st.RMQ(left , right - 1); // O(log N)

    //             if (maxRainfallBetweenYX >= rainfalls[right])
    //             {
    //                 cout << "false" << "\n";
    //             }
    //             else
    //             {
    //                 cout << "maybe" << "\n";
    //             }
    //         }
    //         else if (right == -1)
    //         {
    //             ll maxRainfallBetweenYX = st.RMQ(left + 1, right - 1); // O(log N)

    //             if (maxRainfallBetweenYX >= rainfalls[left])
    //             {
    //                 cout << "false" << "\n";
    //             }
    //             else
    //             {
    //                 cout << "maybe" << "\n";
    //             }
    //         }
    //         else
    //         {
    //             ll maxRainfallBetweenYX = st.RMQ(left + 1, right - 1); // O(log N)

    //             if (rainfalls[right] > rainfalls[left])
    //             {
    //                 cout << "false" << "\n";
    //             }
    //             else if (maxRainfallBetweenYX >= rainfalls[right])
    //             {
    //                 cout << "false" << "\n";
    //             }
    //             else

    //             {
    //                 if (right - left == x - y)
    //                 {
    //                     cout << "true" << "\n";
    //                 }
    //                 else
    //                 {
    //                     cout << "maybe" << "\n";
    //                 }
    //             }
    //         }
    //     }
    // }
}