#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll n, m, a, c, x0;
    cin >> n >> m >> a >> c >> x0;
    vector<ll> arr(n + 1);
    arr[0] = x0;

    for (int i = 1; i < n + 1; i++)
    {
        arr[i] = (a * arr[i - 1] + c) % m;
    }

    arr.erase(arr.begin());

    auto pencarian_biner_anjay = [](vector<ll> &arr, ll k)
    {
        int l = 0, r = arr.size() - 1;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (arr[m] == k)
            {
                return m;
            }
            else if (arr[m] > k)
            {
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return -1;
    };

    ll count = 0;
    for (auto x : arr)
    { // O(nlogn)
        if (pencarian_biner_anjay(arr, x) != -1)
        {
            count++;
        }
    }
    cout << count << endl;
}
