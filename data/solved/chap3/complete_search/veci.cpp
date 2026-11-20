#include <bits/stdc++.h>
using namespace std;

// O(n! * n), n = len(arr)
void permutation(vector<int> arr, int i, vector<vector<int>> &res)
{
    if (i == arr.size())
    {
        res.push_back(arr);
        return;
    }
    
    for (int j = i; j < arr.size(); j++)
    {
        swap(arr[j], arr[i]);
        permutation(arr, i + 1, res);
        swap(arr[j], arr[i]);
    }
}

int main()
{
    int x;
    cin >> x;
    vector<int> arr;
    int xcop = x;
    while (xcop)
    {
        int a = xcop % 10;
        arr.push_back(a);
        xcop = xcop / 10;
    }
    reverse(arr.begin(), arr.end());

    vector<vector<int>> res;
    permutation(arr, 0, res);

    auto ans = 99999999;
    for (auto r : res)
    {
        int num = 0;
        for (int i = 0; i < r.size(); i++)
        {
            num += r[i];
            if (i < r.size() - 1)
            {
                num *= 10;
            }
        }
        if (num > x)
        {
            ans = min(num, ans);
        }
    }
    if (ans == 99999999)
    {
        ans = 0;
    }
    cout << ans << endl;
}