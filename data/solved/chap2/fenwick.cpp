#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/fenwick?tab=metadata

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
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    FenwickTree ft(N);

    while (Q--)
    {
        char op;
        cin >> op;
        if (op == '+')
        {
            int id;
            ll v;
            cin >> id >> v;       // 0<=id<N
            ft.update(id + 1, v); // log(N)
        }
        else
        {
            int i;
            cin >> i; // 1<=i<=N
            if (i == 0)
            {
                cout << "0" << "\n";
                // cout << "0" << endl;
            }
            else
            {
                cout << ft.rsq(i) << "\n";
                // cout << ft.rsq(i) << endl;
            }
        }
    }

    return 0;
}