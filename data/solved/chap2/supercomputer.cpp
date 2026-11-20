#include <bits/stdc++.h>
using namespace std;

int LSOne(int S)
{ // get least significant one-bit of S
    return ((S) & -(S));
}

typedef int bit;

class FenwickTree
{
private:
    vector<bit> ft;

public:
    FenwickTree(int m)
    { // m = size of the original array
        ft.assign(m + 1, 0);
    }

    void build(vector<bit> &freq)
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

    FenwickTree(vector<bit> &freq)
    {
        build(freq);
    }

    FenwickTree(int m, vector<bit> &arr)
    { // m = size of the original array
        vector<bit> freq(m + 1, 0);
        for (int i = 0; i < arr.size(); i++)
        { // O(n)
            ++freq[arr[i]];
        }
        build(freq); // O(m)
    }

    bit rsq(int j)
    { // rsq(1,j)
        bit sum = 0;
        for (; j > 0; j -= LSOne(j))
        { // O(log m)
            sum += ft[j];
        }
        return sum;
    }

    bit rsq(int i, int j)
    {
        return rsq(j) - rsq(i - 1); // O(log m)
    }

    void update(int i, bit v)
    {
        for (i; i < ft.size(); i += LSOne(i))
        {
            ft[i] += v;
        }
    }

    bit select(int k)
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

    bit point_query(int i)
    {
        return ft.rsq(i);
    }

    void range_update(int ui, int uj, bit v)
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

    bit rsq(int j)
    {
        return rupq.point_query(j) * j - purq.rsq(j);
    }

    void range_update(int ui, int uj, bit v)
    {
        rupq.range_update(ui, uj, v);
        purq.update(ui, v * (ui - 1));
        purq.update(uj + 1, -v * uj);
    }
};

int main()
{
    int N, K;
    cin >> N >> K;

    FenwickTree ft(N);

    for (int i = 0; i < K; i++)
    { // O(K * log(N))
        char cmdType;
        cin >> cmdType;
        if (cmdType == 'F')
        {
            int ithBit;
            cin >> ithBit;
            int currentValIthBit = ft.rsq(ithBit, ithBit); // O(log N)
            if (currentValIthBit)
            { // flip the i-th bit
                ft.update(ithBit, -1); // O(log N)
            }
            else
            {
                ft.update(ithBit, 1); // O(log N)
            }
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << ft.rsq(l, r) << "\n"; // O(log N)
        }
    }
}

