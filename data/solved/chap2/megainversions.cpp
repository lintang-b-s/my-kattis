#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> sorted_arr(arr.begin(), arr.end());
    sort(sorted_arr.begin(), sorted_arr.end());
    vector<int> sorted_rev_arr(arr.begin(), arr.end());
    sort(sorted_rev_arr.begin(), sorted_rev_arr.end(), greater<int>());

    vector<int> posisi_naik(1e5);
    vector<int> posisi_turun(1e5);
    for (int i = 0; i < n; i++)
    {
        posisi_naik[sorted_arr[i]] = i + 1;
        posisi_turun[sorted_rev_arr[i]] = i + 1;
    }

    FenwickTree ft(n);
    vector<ll> bigger_than(n);
    vector<ll> smaller_than(n);

    // fenwick tree O(nlgn)
    for (int i = n - 1; i >= 0; i--)
    {
        int ai = arr[i];
        int r = posisi_naik[ai];
        ll smaller_count = ft.rsq(r - 1); // O(lgn)
        ft.update(r, 1);                  // O(lgn)
        smaller_than[i] = smaller_count;
    }

    ft = FenwickTree(n);
    ll count = 0; // upperbound for triple inversions C(n,3)

    for (int i = 0; i < n; i++)
    {
        auto ai = arr[i];
        int r = posisi_turun[ai];
        ll bigger_count = ft.rsq(r - 1); // O(lgn)
        ft.update(r, 1);                 // O(lgn)
        count += bigger_count * smaller_than[i];
    }
    cout << count << endl;
}

// TLE
// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> arr(n);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> arr[i];
//     }

//     // naive O(n^2)
//     ll count = 0; // upperbound for triple inversions C(n,3)
//     for (int j = 0; j < n; j++)
//     {
//         int aj = arr[j];
//         int ai = 0;
//         int l = 0;
//         for (int i = 0; i < j; i++)
//         {
//             if (arr[i] > aj)
//             {
//                 ai = arr[i];
//                 l++;
//             }
//         }
//         int ak = 1e6;
//         int r = 0;
//         for (int k = j + 1; k < n; k++)
//         {

//             if (arr[k] < aj)
//             {
//                 ak = arr[k];
//                 r++;
//             }
//         }

//         if (ai > aj && aj > ak)
//         {
//             count += l * r;
//         }
//     }
//     cout << count << endl;
// }