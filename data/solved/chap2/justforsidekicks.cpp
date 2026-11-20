#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/justforsidekicks?tab=metadata

int LSOne(int S)
{ // get least significant one-bit of S
    return ((S) & -(S));
}

typedef long long ll;

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
    int N, Q;
    cin >> N >> Q;

    vector<FenwickTree> fts(6, FenwickTree(N));

    unordered_map<int, ll> gemValues;

    for (int i = 0; i < 6; i++)
    {
        int vi;

        cin >> vi;
        gemValues[i] = vi;
    }

    string gems;
    cin >> gems;
    for (int i = 0; i < N; i++)
    {
        int gemType = gems[i] - '0';
        fts[gemType - 1].update(i + 1, 1);
    }

    while (Q--)
    {
        int cmdType;
        cin >> cmdType;
        if (cmdType == 3)
        {
            int l, r;
            cin >> l >> r;

            ll sum = 0;
            for (int vi = 0; vi < 6; vi++)
            {// O(log N)
                int freq = fts[vi].rsq(l, r); // O(log N)
                sum += freq * gemValues[vi];
            }

            cout << sum << "\n";
        }
        else if (cmdType == 1)
        {
            int k, p;
            cin >> k >> p;
            int oldGemType = gems[k - 1] - '0';
            fts[oldGemType - 1].update(k, -1); // O(log N)
            gems[k - 1] = p + '0';
            fts[p - 1].update(k, 1); // O(log N)
        }
        else
        {
            int pi, vi;
            cin >> pi >> vi;
            gemValues[pi - 1] = vi;
        }
    }

    // TLE
    // while (Q--)
    // {
    //     int cmdType;
    //     cin >> cmdType;
    //     if (cmdType == 3)
    //     {
    //         int l, r;
    //         cin >> l >> r;

    //         ll sum = 0;
    //         for (; l <= r; l++)
    //         {
    //             int gemType = gems[l - 1] - '0';
    //             int freq = fts[gemType - 1].rsq(l, l);
    //             sum += freq * gemValues[gemType - 1];
    //         }
    //         cout << sum << "\n";
    //     }
    //     else if (cmdType == 1)
    //     {
    //         int k, p;
    //         cin >> k >> p;
    //         int oldGemType = gems[k - 1] - '0';
    //         fts[oldGemType-1].update(k, -1);
    //         gems[k - 1] = p + '0';
    //         fts[p - 1].update(k, 1);
    //     }
    //     else
    //     {
    //         int pi, vi;
    //         cin >> pi >> vi;
    //         gemValues[pi - 1] = vi;
    //     }
    // }

    return 0;
}