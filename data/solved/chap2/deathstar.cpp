#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/deathstar?tab=metadata
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> arr(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int a;
            cin >> a;
            arr[i][j] = a;
        }
    }

    vector<int> ans(n, 0);

    // O(n^2)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans[i] |= arr[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << ans[i];
        if (i < n - 1)
        {
            cout << ' ';
        }
    }
}