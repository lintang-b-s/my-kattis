#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/pivot?tab=metadata
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        arr[i] = a;
    }
    vector<int> ans(0);

    vector<int> prefixMax(n), suffixMin(n);

    int prefixMaxNum = 0;
    for (int i = 0; i < n; i++)
    { // O(n)
        prefixMaxNum = max(prefixMaxNum, arr[i]);
        prefixMax[i] = prefixMaxNum;
    }

    int suffixMinNum = 100000;
    for (int i = n - 1; i >= 0; i--)
    { // O(n)
        suffixMinNum = min(suffixMinNum, arr[i]);
        suffixMin[i] = suffixMinNum;
    }

    for (int i = 0; i < n; i++)
    { // O(n)
        if (suffixMin[i] >= arr[i] && prefixMax[i] <= arr[i])
        {
            ans.push_back(arr[i]);
        }
    }
    cout << ans.size();
    // for (int i = 0; i < n; i++)
    // { // O(n^2)
    //     bool afkhBisaMenjadiPivot = true;
    //     for (int j = 0; j < i; j++)
    //     {
    //         if (arr[j] > arr[i])
    //         {
    //             afkhBisaMenjadiPivot = false;
    //         }
    //     }

    //     for (int j = i + 1; j < n; j++)
    //     {
    //         if (arr[j] < arr[i])
    //         {
    //             afkhBisaMenjadiPivot = false;
    //         }
    //     }
    //     if (afkhBisaMenjadiPivot) {
    //         ans.push_back(arr[i]);
    //     }
    // }
    // cout << ans.size();
}