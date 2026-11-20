#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> paint_sizes(n);
    vector<int> joe_paint_needs(m);
    for (int i = 0; i < n; i++)
    {
        cin >> paint_sizes[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> joe_paint_needs[i];
    }

    sort(paint_sizes.begin(), paint_sizes.end());

    auto my_upper_bound = [](vector<int> &arr, int k)
    {
        int l = 0, r = arr.size() - 1;
        int ans = -1;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (arr[m] >= k)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return ans;
    };

    ll sisa = 0;
    for (auto jp : joe_paint_needs)
    { // O(m*log n)
        int j = my_upper_bound(paint_sizes, jp);
        sisa += paint_sizes[j] - jp;
    }
    cout << sisa << endl;
}