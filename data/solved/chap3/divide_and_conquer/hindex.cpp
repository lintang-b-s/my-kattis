#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// https://open.kattis.com/problems/hindex
ll bn_upper_bound(vector<ll> &arr, ll h)
{
    int l = 0, r = arr.size() - 1;
    ll j = arr.size();
    while (l <= r)
    {
        ll m = (l + r) / 2;
        if (arr[m] >= h)
        {
            j = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    return j;
}

int main()
{
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    ll biggest_citation = arr[n - 1];

    ll h_index = 0;
    for (int h = 0; h <= n; h++)
    { // O(n*logn)
        ll j = bn_upper_bound(arr, h);
        if ((n - j) >= h)
        {
            ll curr_h_index = h;
            h_index = max(h_index, curr_h_index);
        }
    }
    cout << h_index << endl;
}



