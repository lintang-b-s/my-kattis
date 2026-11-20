#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/turbo?tab=metadata

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
    int N;
    cin >> N;
    vector<int> arr(N);
    vector<int> posisi(N + 1);
    FenwickTree ft(N);

    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        arr[i] = a;
        posisi[a] = i + 1;
        ft.update(i + 1, 1);
    }

    int v = 1;
    int rightMost = 0;
    int leftMost = 1;

    for (int i = 0; i < N; i++)
    { // O(N * log N)

        int swapCount = 0;

        if ((i + 1) % 2 == 0)
        {

            swapCount = ft.rsq(posisi[v] + 1, N);  // O(log N)
            ft.update(posisi[v], -1); // O(log N)

            // left most
            v = 1 + leftMost;
            leftMost++;
        }
        else
        {

            swapCount = ft.rsq(posisi[v] - 1);
            ft.update(posisi[v], -1);

            // right most
            v = N - rightMost;
            rightMost++;
        }
        cout << swapCount << endl;
    }

    // TLE
    // int v = 1;
    // int rightMost = 0;
    // int leftMost = 1;

    // for (int i = 0; i < N; i++)
    // { // O(N^2)
    //     int posisiV = 0;
    //     for (int j = 0; j < N; j++)
    //     {
    //         if (arr[j] == v)
    //         {
    //             posisiV = j;
    //         }
    //     }

    //     int swapCount = 0;
    //     if (i % 2 == 0)
    //     {
    //         for (int j = posisiV; j >= v; j--)
    //         {
    //             swap(arr[j], arr[j - 1]);
    //             swapCount++;
    //         }
    //     }
    //     else
    //     {
    //         for (int j = posisiV; j < v - 1; j++)
    //         {
    //             swap(arr[j], arr[j + 1]);
    //             swapCount++;
    //         }
    //     }
    //     if ((i + 1) % 2 == 0)
    //     {
    //         // left most
    //         v = 1 + leftMost;
    //         leftMost++;
    //     }
    //     else
    //     {
    //         // right most
    //         v = N - rightMost;
    //         rightMost++;
    //     }
    //     cout << swapCount << endl;
    // }
}