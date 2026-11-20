#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/moviecollection?tab=metadata

int LSOne(int S)
{ // get least significant one-bit of S
    return ((S) & -(S));
}

typedef int ll;

class FenwickTree
{
private:
    vector<ll> ft;

public:
    FenwickTree(int m)
    { // m = size of the original array
        ft.assign(m + 1, 0);
    }

    void build(vector<ll> &freq)
    {
        int m = freq.size() - 1;
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; i++)
        { // O(m)
            ft[i] += freq[i];
            if (i + LSOne(i) <= m)
            {
                ft[i + LSOne(i)] += ft[i];
            }
        }
    }

    FenwickTree(vector<ll> &freq)
    {
        build(freq);
    }

    FenwickTree(int m, vector<ll> &arr)
    { // m = size of the original array
        vector<ll> freq(m + 1, 0);
        for (int i = 0; i < arr.size(); i++)
        { // O(n)
            ++freq[arr[i]];
        }
        build(freq); // O(m)
    }

    ll rsq(int j)
    { // rsq(1,j)
        ll sum = 0;
        for (; j > 0; j -= LSOne(j))
        { // O(log m)
            sum += ft[j];
        }
        return sum;
    }

    ll rsq(int i, int j)
    {
        return rsq(j) - rsq(i - 1); // O(log m)
    }

    void update(int i, ll v)
    {
        for (i; i < ft.size(); i += LSOne(i))
        {
            ft[i] += v;
        }
    }

    ll select(int k)
    { // O(log m)
        int p = 1;
        while (p * 2 < ft.size())
        {
            p *= 2;
        }

        int i = 0;
        while (p)
        {
            if (k > ft[i + p])
            {
                k -= ft[i + p];
                i += p;
            }
            p /= 2;
        }

        return i + 1;
    }
};

class RUPQ
{
private:
    FenwickTree ft;

public:
    RUPQ(int m) : ft(FenwickTree(m))
    {
    }

    ll point_query(int i)
    {
        return ft.rsq(i);
    }

    void range_update(int ui, int uj, ll v)
    {
        ft.update(ui, v);
        ft.update(uj + 1, -v);
    }
};

class RURQ
{
private:
    FenwickTree purq;
    RUPQ rupq;

public:
    RURQ(int m) : purq(FenwickTree(m)), rupq(RUPQ(m))
    {
    }

    ll rsq(int j)
    {
        return rupq.point_query(j) * j - purq.rsq(j);
    }

    void range_update(int ui, int uj, ll v)
    {
        rupq.range_update(ui, uj, v);
        purq.update(ui, v * (ui - 1));
        purq.update(uj + 1, -v * uj);
    }
};

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int m, r;
        cin >> m >> r;

        int moviesMap[m + 1];
        vector<ll> freq(m + r + 1, 0); // last m is the movies a1,a2,...,am

        for (int i = 1; i <= m; i++)
        { // O(m)
            moviesMap[i] = r + i;
        }

        for (int i = r + 1; i <= m + r; i++)
        { // O(m)
            freq[i] = 1;
        }

        FenwickTree ft(freq);

        int newPos = r;
        for (int i = 0; i < r; i++)
        { // O(r*log (m+r))
            int query;
            cin >> query;

            int queryId = moviesMap[query];
            int moviesAbove = ft.rsq(queryId - 1); // O(log (m+r))
            cout << moviesAbove << " ";

            ft.update(queryId, -1); // O(log (m+r))

            moviesMap[query] = newPos;
            newPos--;
            ft.update(moviesMap[query], 1); // O(log (m+r))
        }
        cout << "\n";
    }

    // O(r* (m+log m)), got TLE
    // while (t--)
    // {
    //     int m, r;
    //     cin >> m >> r;

    //     int moviesMap[m + 1];
    //     vector<ll> freq(m + 1, 0);

    //     for (int i = 1; i <= m; i++)
    //     {// O(m)
    //         moviesMap[i] = i;
    //         if (i > 1)
    //         {
    //             freq[i] = 1;
    //         }
    //     }

    //     FenwickTree ft(freq);

    //     for (int i = 0; i < r; i++)
    //     { // O(r* (m+log m)), got TLE
    //         int query;
    //         cin >> query;

    //         int queryId = moviesMap[query];
    //         int moviesAbove = ft.rsq(queryId); // O(log m)
    //         cout << moviesAbove << " ";

    //         if (moviesMap[query] != 1)
    //         {
    //             moviesMap[query] = 1;
    //             for (int j = 0; j < m; j++)
    //             { // O(m)
    //                 if (j == query)
    //                 {
    //                     continue;
    //                 }
    //                 moviesMap[j]++;
    //             }
    //         }
    //     }
    //     cout << "\n";
    // }

    return 0;
}